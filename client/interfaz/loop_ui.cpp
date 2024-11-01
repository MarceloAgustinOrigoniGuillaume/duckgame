#include "loop_ui.h"

UILoop::UILoop(ActionListener& dtoSender, SimpleEventListener& _events,
               const GameContext& gameContext):
        sdlLib(SDL_INIT_VIDEO),
        window("UILOOP demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        animation(gameContext),
        eventHandler(dtoSender, gameContext),
        matchDtoQueue(_events),
        lastUpdate(),
        isRunning_(true),
        playerId(gameContext.first_player) {}

void UILoop::exec() {
    try {
        while (isRunning_) {
            unsigned int frameStart = SDL_GetTicks();

            eventHandler.handle(isRunning_);

            update();

            draw();

            frameDelay(frameStart);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in UILoop::exec: " << e.what() << std::endl;
        isRunning_ = false;
    } catch (...) {
        std::cerr << "Unknown exception caught in UILoop::exec" << std::endl;
        isRunning_ = false;
    }
}

void UILoop::update() {

    MatchDto matchUpdate;

    if (matchDtoQueue.try_update(matchUpdate)) {
        lastUpdate = matchUpdate;
        if (matchUpdate.info.estado == TERMINADA) {
            isRunning_ = false;
        }
    }

    animation.updateFrame();

    animation.updateSprite(lastUpdate);
}

void UILoop::draw() {
    // Clear screen
    renderer.SetDrawColor(255, 255, 255, 255);  // White background
    renderer.Clear();

    const PlayerDTO* mainPlayer = nullptr;

    for (const PlayerDTO& player: lastUpdate.players) {
        if (player.id == playerId) {
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

void UILoop::drawPlayer(const PlayerDTO& player) {
    // Determine the flip mode based on the last direction
    SDL_RendererFlip flip = animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Draw player sprite
    renderer.Copy(textures.getTexture(player.id),
                  SDL2pp::Rect(animation.getSpriteX(player.id), animation.getSpriteY(player.id),
                               SPRITE_WIDTH, SPRITE_HEIGHT),
                  SDL2pp::Rect(player.coord_x, player.coord_y, 50, 50), 0.0, SDL2pp::Point(0, 0),
                  flip);
}

void UILoop::frameDelay(unsigned int frameStart) {
    unsigned int frameTime = SDL_GetTicks() - frameStart;
    if (FRAME_DELAY > frameTime) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

UILoop::~UILoop() = default;
