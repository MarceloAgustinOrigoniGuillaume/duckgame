#ifndef CLIENT_UI_LOOP_H_
#define CLIENT_UI_LOOP_H_

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/actionlistener.h"
#include "client/gamecontext.h"
#include "client/simpleeventlistener.h"
#include "common/dtos.h"
#include "common/dtosplayer.h"

#include "animation.h"
#include "texture_container.h"

#define SCREEN_HEIGHT 480
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define FRAME_DELAY 16
#define GROUND_Y 400
#define TWO_PLAYERS true

class UILoop {
private:
    SDL2pp::SDL sdlLib;

    SDL2pp::Window window;

    SDL2pp::Renderer renderer;

    TextureContainer textures;  // Procesado de todas las imagenes del juego

    Animation animation;

    ActionListener& sender;

    SimpleEventListener& matchDtoQueue;

    MatchDto lastUpdate;

    const GameContext& context;

    bool isRunning_;  // cppcheck-suppress unusedStructMember

    // Event processing:
    // - If window is closed, or Q or Escape buttons are pressed, quit the
    // application
    // - If Right key is pressed, character would run
    // - If Right key is released, character would stop
    // - If Space key is pressed, character would jump
    // - If Down key is pressed, character would lay dead
    void handleEvent();

    // This is where most of the game logic will go;
    // including: movement, AI, and animation updates.
    void update();

    // Once all the entities have been updated, we draw them to the screen.
    // This method will be responsible for drawing everything, including the games
    // UI.
    void draw();

    void drawPlayer(const PlayerDTO& player);

    void frameDelay(unsigned int frameStart);

public:
    UILoop(ActionListener& dtoSender, SimpleEventListener& _events, const GameContext& gameContext);

    void exec();

    ~UILoop();
};

#endif  // CLIENT_UI_LOOP_H_