#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer, gameContext.map.textures),
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
}

void Drawer::drawBackground() {
    int scaledWidth = camera.backgroundScaledSize(SCREEN_WIDTH);
    int scaledHeight = camera.backgroundScaledSize(SCREEN_HEIGHT);

    renderer.Copy(textures.getTexture(TextureType::BACKGROUND),
                  SDL2pp::Rect((SCREEN_WIDTH - scaledWidth) / 2, (SCREEN_HEIGHT - scaledHeight) / 2,
                               scaledWidth, scaledHeight),
                  SDL2pp::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void Drawer::drawObjects() {
    // inicialmente dibujo solo los primeros 4 elementos del .yaml
    for (const MapObject& object: context.map.objects) {
        renderer.Copy(
                textures.getBlockTexture(object.ind_texture), SDL2pp::Rect(0, 0, 73, 93),
                SDL2pp::Rect(camera.getScreenX(object.column * 16),  // 16 es el size de una unidad?
                             camera.getScreenY(object.row * 16), camera.getScaledSize(16),
                             camera.getScaledSize(16)));
    }
}

void Drawer::draw(const MatchDto& matchDto) {
    // Clear screen
    renderer.SetDrawColor(255, 255, 255, 255);  // White background
    renderer.Clear();

    drawBackground();

    drawObjects();

    // dibujo los objetos de la partida -> luego agregar en una funcion
    for (const auto& object: matchDto.objects) {
        renderer.Copy(textures.getTexture(TextureType::BOX), SDL2pp::Rect(0, 16, 16, 16),
                      SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                   camera.getScaledSize(16), camera.getScaledSize(16)));
    }

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
