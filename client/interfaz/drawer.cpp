#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        window(window),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        animation(animation),
        camera(camera),
        context(gameContext),
        startTime(std::chrono::steady_clock::now()),
        showIndicators(true) {}

void Drawer::drawPlayer(const PlayerDTO& player) {
    static const std::unordered_map<int, std::string> duckTextures = {
            {1, TextureContainer::WHITE_DUCK},
            {2, TextureContainer::YELLOW_DUCK},
            {3, TextureContainer::GREY_DUCK},
            {4, TextureContainer::ORANGE_DUCK}};

    auto mappedTexture = duckTextures.find(player.id);
    if (mappedTexture != duckTextures.end()) {
        const auto& playerTexture = mappedTexture->second;

        SDL_RendererFlip flip =
                animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        renderer.Copy(
                textures.getTexture(playerTexture),
                SDL2pp::Rect(animation.getSpriteX(player.id),
                             animation.getSpriteY(player.id),
                             SPRITE_SIZE,
                             SPRITE_SIZE
                             ),
                SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER),
                             camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 16),
                             camera.getScaledSize(SPRITE_SIZE),
                             camera.getScaledSize(SPRITE_SIZE)
                             ),
                0.0, SDL2pp::Point(0, 0), flip);

        if (player.weapon != TypeWeapon::NONE) {
            drawWeapon(player, flip);
        }

        drawArmor(player, flip);
    }
}

void Drawer::drawIndicator(const PlayerDTO& player, bool isMainPlayer) {
    SDL2pp::Rect indicatorType;

    float spriteX = animation.getIndicatorSprite(INDICATOR_WIDTH);

    if (isMainPlayer) {
        indicatorType = SDL2pp::Rect(spriteX, 0, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    } else {
        indicatorType = SDL2pp::Rect(spriteX, INDICATOR_HEIGHT, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    }

    renderer.Copy(
            textures.getTexture(TextureContainer::PLAYER_INDICATOR), indicatorType,
            SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER + 9),
                         camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 40),
                         camera.getScaledSize(INDICATOR_WIDTH_RESIZED),
                         camera.getScaledSize(INDICATOR_HEIGHT_RESIZED)));
}

void Drawer::drawArmor(const PlayerDTO& player, SDL_RendererFlip flip) {

    if (player.helmet) {
        renderer.Copy(
                textures.getTexture(TextureContainer::HELMET_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(
                        camera.getScreenX(player.pos.x + getTextureFlipValue(flip, HELMET_FLIP_X,
                                                                             HELMET_UNFLIP_X)),
                        camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 10), camera.getScaledSize(SPRITE_SIZE),
                        camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);
    }


    if (player.chest_armor) {
        renderer.Copy(
                textures.getTexture(TextureContainer::CHEST_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(camera.getScreenX(player.pos.x), camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER + 3),
                             camera.getScaledSize(SPRITE_SIZE), camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);
    }
}

void Drawer::drawWeapon(const PlayerDTO& player, SDL_RendererFlip flip) {
    static const std::unordered_map<TypeWeapon, std::tuple<std::string, int, int>> weaponTextures =
            {
                    // almaceno enum de textura del container y dimensiones
                    {TypeWeapon::PISTOLA_COWBOY,
                     {TextureContainer::COWBOY_GUN, COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT}},
                    {TypeWeapon::PEW_PEW_LASER,
                     {TextureContainer::PEW_PEW_LASER, PEW_PEW_LASER_SIZE, PEW_PEW_LASER_SIZE}},
                    {TypeWeapon::MAGNUM, {TextureContainer::MAGNUM, MAGNUM_SIZE, MAGNUM_SIZE}}
                    // demas armas
            };

    auto weaponTexture = weaponTextures.find(player.weapon);
    if (weaponTexture != weaponTextures.end()) {
        const auto& [textureType, width, height] = weaponTexture->second;

        renderer.Copy(
                textures.getTexture(textureType), SDL2pp::Rect(0, 0, width, height),
                SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER + getTextureFlipValue(flip, GUN_FLIP_X, GUN_UNFLIP_X)),
                             camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER + 3),
                             camera.getScaledSize(width - 6),
                             camera.getScaledSize(height - 6)),
                0.0, SDL2pp::Point(0, 0), flip);
    }
}

int Drawer::getTextureFlipValue(SDL_RendererFlip flip, int flipValue, int unflipValue) {
    return flip == SDL_FLIP_HORIZONTAL ? flipValue : unflipValue;
}

void Drawer::drawBackground() {
    const float PARALLAX_OFFSET_FACTOR = 0.5f;
    int windowWidth = window.GetWidth();
    int windowHeight = window.GetHeight();

    SDL_Rect visibleSection =
            camera.backgroundVisibleSection(windowWidth, windowHeight, PARALLAX_OFFSET_FACTOR);

    renderer.Copy(
            textures.getTexture(context.map.background),
            SDL2pp::Rect(visibleSection.x, visibleSection.y, visibleSection.w, visibleSection.h),
            SDL2pp::Rect(0, 0, windowWidth, windowHeight));
}

void Drawer::drawObjects(const MatchDto& matchDto) {
    for (const MapObject& object: context.map.objects) {
        renderer.Copy(
                textures.getTexture(object.texture), SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
                SDL2pp::Rect(camera.getScreenX(object.column * BLOCK_WIDTH),
                             camera.getScreenY(-object.row * BLOCK_HEIGHT),
                             camera.getScaledSize(BLOCK_WIDTH),
                             camera.getScaledSize(BLOCK_HEIGHT)));
    }

    for (const auto& object:
         matchDto.objects) {  // modificar por switch cuando se agreguen todos los objetos
        if (object.type == TypeDynamicObject::BOX) {
            renderer.Copy(
                    textures.getTexture(context.map.boxes_tex),
                    SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x),
                                 camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(BLOCK_WIDTH),
                                 camera.getScaledSize(BLOCK_HEIGHT)
                                )
                    );

        } else if (object.type == TypeDynamicObject::PROJECTILE) {
            renderer.Copy(
                    textures.getTexture(TextureContainer::PISTOL_BULLET), SDL2pp::Rect(0, 0, 3, 8),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(3), camera.getScaledSize(8)));

        } else if (object.type == TypeDynamicObject::PISTOLA_COWBOY) {
            renderer.Copy(
                    textures.getTexture(TextureContainer::COWBOY_GUN),
                    SDL2pp::Rect(0, 0, COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(COWBOY_GUN_WIDTH - 6),
                                 camera.getScaledSize(COWBOY_GUN_HEIGHT - 6)));
        } else if (object.type == TypeDynamicObject::LASER) {
            renderer.Copy(
                    textures.getTexture(TextureContainer::LASER_BEAM), SDL2pp::Rect(0, 0, 1, 8),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(1), camera.getScaledSize(8)));
        }
    }
}

void Drawer::updateIndicatorFlag() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime =
            std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    showIndicators = elapsedTime < INDICATOR_MAX_TIME;
}

void Drawer::draw(const MatchDto& matchDto) {
    renderer.Clear();

    drawBackground();

    drawObjects(matchDto);

    updateIndicatorFlag();

    for (const PlayerDTO& player: matchDto.players) {

        if (showIndicators) {
            if (player.id == context.first_player) {
                drawIndicator(player, IS_MAIN_PLAYER);
            } else if ((context.dualplay) && (player.id == context.second_player)) {
                drawIndicator(player, IS_SECONDARY_PLAYER);
            }
        }

        drawPlayer(player);
    }

    // Show rendered frame
    renderer.Present();
}

/*void Drawer::drawLeaderboard(const MatchStatsInfo& matchStats) {
    renderer.Clear();

    drawBackground();

    static const std::unordered_map<int, std::string> duckTextures = {
            {1, TextureContainer::YELLOW_DUCK},
            {2, TextureContainer::GREY_DUCK},
            {3, TextureContainer::ORANGE_DUCK},
            {4, TextureContainer::WHITE_DUCK}};


    renderer.Copy(textures.getTexture(TextureContainer::SCOREBOARD), SDL2pp::Rect(0, 0, 320, 200),
                  SDL2pp::Rect(50, 50, 520, 400));

    int y = 110;
    int x = 8;

    for (const PlayerStatDto& playerStat: matchStats.stats) {
        std::cout << static_cast<int>(playerStat.id) << std::endl;
        auto mappedTexture = duckTextures.find(static_cast<int>(playerStat.id));
        if (mappedTexture != duckTextures.end()) {
            const auto& playerTexture = mappedTexture->second;

            renderer.Copy(  // jugador
                    textures.getTexture(playerTexture),
                    SDL2pp::Rect(1, 10, SPRITE_SIZE, SPRITE_SIZE), SDL2pp::Rect(165, y, 64, 64));

            renderer.Copy(  // rondas ganadas
                    textures.getTexture(TextureContainer::FONT),
                    SDL2pp::Rect(x * (static_cast<int>(playerStat.wins)), 8, 8, 8),
                    SDL2pp::Rect(320, y + 15, 20, 20));  // modificar x
        }

        y += 50;
    }

    // Show rendered frame
    renderer.Present();
}*/

Drawer::~Drawer() = default;
