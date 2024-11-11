#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        window(window),
        textures(renderer),
        animation(animation),
        camera(camera),
        context(gameContext) {}

void Drawer::drawPlayer(const PlayerDTO& player) {
    SDL_RendererFlip flip = animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    renderer.Copy(
            textures.getTexture(player.id),
            SDL2pp::Rect(animation.getSpriteX(player.id), animation.getSpriteY(player.id),
                         SPRITE_WIDTH, SPRITE_HEIGHT),
            SDL2pp::Rect(camera.getScreenX(player.pos.x), camera.getScreenY(player.pos.y),
                         camera.getScaledSize(SPRITE_WIDTH), camera.getScaledSize(SPRITE_HEIGHT)),
            0.0, SDL2pp::Point(0, 0), flip);

    drawWeapon(player, flip);
}

void Drawer::drawWeapon(const PlayerDTO& player, SDL_RendererFlip flip) {
    static const std::unordered_map<TypeWeapon, std::tuple<TextureType, int, int>> weaponTextures =
            {
                    // almaceno enum de textura del container y dimensiones
                    {TypeWeapon::PISTOLA_COWBOY,
                     {TextureType::COWBOY_GUN, COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT}}
                    // demas armas
            };

    auto weaponTexture = weaponTextures.find(player.weapon);
    if (weaponTexture != weaponTextures.end()) {
        const auto& [textureType, width, height] = weaponTexture->second;

        renderer.Copy(
                textures.getTexture(textureType), SDL2pp::Rect(0, 0, width, height),
                SDL2pp::Rect(camera.getScreenX(player.pos.x + getWeaponFlip(flip)),
                             camera.getScreenY(player.pos.y + (SPRITE_HEIGHT / 2)),
                             camera.getScaledSize(width - 6), camera.getScaledSize(height - 6)),
                0.0, SDL2pp::Point(0, 0), flip);
    }
}

int Drawer::getWeaponFlip(SDL_RendererFlip flip) {
    return flip == SDL_FLIP_HORIZONTAL ? FLIP : UNFLIP;
}

void Drawer::drawMap() {
    Map map;

    map.drawBackground(*this);
    map.drawBlocks(*this);
    map.drawDecorations(*this);
    map.drawSpawnPlayers(*this);
    map.drawSpawnWeapons(*this);
}

void Drawer::drawBackground(MapObjectData mapObject) {
    auto [windowWidth, windowHeight] = window.GetSize();

    int scaledWidth = camera.backgroundScaledSize(windowWidth);
    int scaledHeight = camera.backgroundScaledSize(windowHeight);

    renderer.Copy(textures.getMapTexture(mapObject.texture),
                SDL2pp::Rect(
                    (windowWidth - scaledWidth) / 2,
                    (windowHeight - scaledHeight) / 2,
                    scaledWidth,
                    scaledHeight
                ),
                SDL2pp::Rect(0, 0, windowWidth, windowHeight));
}

void Drawer::drawMapObject(MapObjectData mapObject) {
    renderer.Copy(
            textures.getMapTexture(mapObject.texture), SDL2pp::Rect(0, 0, 16, 16),
            SDL2pp::Rect(camera.getScreenX(mapObject.column * 16), camera.getScreenY(mapObject.row * 16),
                            camera.getScaledSize(16), camera.getScaledSize(16)));
}

void Drawer::drawObjects(const MatchDto& matchDto) {
    // inicialmente dibujo solo los primeros 4 elementos del .yaml
    /*for (int i = 0; i < 4; i++) {

        renderer.Copy(textures.getTexture((int)context.blocks[i].texture),
                      SDL2pp::Rect(0, 0, 73, 93),
                      SDL2pp::Rect(camera.getScreenX(context.blocks[i].pos.x),
                                   camera.getScreenY(context.blocks[i].pos.y),
                                   camera.getScaledSize(73), camera.getScaledSize(93)));
    }*/

    // dibujo los objetos de la partida -> luego agregar en una funcion
    for (const auto& object: matchDto.objects) {

        if (object.type == TypeDynamicObject::BOX) {
            renderer.Copy(
                    textures.getTexture(TextureType::BOX), SDL2pp::Rect(0, 16, 16, 16),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(16), camera.getScaledSize(16)));

        } else if (object.type == TypeDynamicObject::PISTOLA_COWBOY) {
            renderer.Copy(
                    textures.getTexture(TextureType::COWBOY_GUN), SDL2pp::Rect(0, 0, 22, 11),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(22 - 6), camera.getScaledSize(11 - 6)));
        }
    }
}

void Drawer::draw(const MatchDto& matchDto) {
    // Clear screen
    renderer.SetDrawColor(255, 255, 255, 255);  // White background
    renderer.Clear();

    drawMap();

    drawObjects(matchDto);

    const PlayerDTO* mainPlayer = nullptr;

    for (const PlayerDTO& player: matchDto.players) {
        if (player.id == context.first_player) {
            mainPlayer = &player;
            continue;
        }
        drawPlayer(player);
    }

    if (mainPlayer) {
        drawPlayer(*mainPlayer);
    }

    // Show rendered frame
    renderer.Present();
}

Drawer::~Drawer() = default;
