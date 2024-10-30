#include "client.h"

#include "./simpleeventlistener.h"

Client::Client(int argc, char* argv[]): argc(argc), argv(argv) {}

int Client::execMenu(LobbyConnector& connector) {
    MenuHandler menuHandler(connector);

    QApplication application(argc, argv);
    //-------
    QPalette darkTheme;
    darkTheme.setColor(QPalette::Window, QColor(53, 53, 53));
    darkTheme.setColor(QPalette::WindowText, Qt::white);
    darkTheme.setColor(QPalette::Base, QColor(25, 25, 25));
    darkTheme.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkTheme.setColor(QPalette::ToolTipBase, Qt::white);
    darkTheme.setColor(QPalette::ToolTipText, Qt::white);
    darkTheme.setColor(QPalette::Text, Qt::white);
    darkTheme.setColor(QPalette::Button, QColor(53, 53, 53));
    darkTheme.setColor(QPalette::ButtonText, Qt::white);
    darkTheme.setColor(QPalette::BrightText, Qt::red);
    darkTheme.setColor(QPalette::Link, QColor(42, 130, 218));
    darkTheme.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkTheme.setColor(QPalette::HighlightedText, Qt::black);
    application.setPalette(darkTheme);
    //------
    Menu menu(menuHandler);
    menu.show();
    return application.exec();
}
int Client::exec() {
    GameContext context;
    LobbyConnector connector(context);
    if (execMenu(connector) != 0) {
        return 1;
    }

    // Si no esta empezada la partida no muestres el sdl, sali.
    if (!context.started) {
        std::cerr << "Did not start a match, exiting..." << std::endl;
        return 1;
    }

    // if (execGame(gameLoop) != 0) {
    //     return 1;
    // }

    return execGame(connector, context);
}


int Client::execGame(LobbyConnector& connector, const GameContext& context) {
    // Crear event queue iniciar action listener y exec del uiloop!
    SimpleEventListener listener;

    GameActionSender& actionListener(*connector.initGame(listener));
    actionListener.begin();

    if (context.dualplay) {
        std::cout << "Dos jugadores!!! " << (int)context.first_player << " y "
                  << (int)context.second_player << " TOTAL " << (int)context.cantidadjugadores
                  << std::endl;
    } else {
        // Solo un jugador
        std::cout << "Un solo jugador!!! " << (int)context.first_player << " TOTAL "
                  << (int)context.cantidadjugadores << std::endl;
    }

    UILoop uiLoop(actionListener, listener, context);

    uiLoop.exec();


    return connector.cangonext() ? 0 : -1;
}

Client::~Client() {}
