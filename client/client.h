#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <QStyleFactory>
#include <string>

#include "./gamecontext.h"
#include "client/core/lobby_connector.h"
#include "interfaz/loop_ui.h"
#include "menu/menu.h"
#include "menu/menuhandler.h"
//#include "client/core/game_action_sender.h"


class Client {
private:
    int argc;     // cppcheck-suppress unusedStructMember
    char** argv;  // cppcheck-suppress unusedStructMember

    int execMenu(LobbyConnector& connector);
    int execGame(LobbyConnector& connector, const GameContext& context);

public:
    explicit Client(int argc, char* argv[]);

    int exec();


    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;

    ~Client();
};

#endif
