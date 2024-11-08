#include "./lobby_create_state.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "./lobby_action_sender.h"
#include "common/core/liberror.h"
#include "common/protocolerror.h"


LobbyCreateState::LobbyCreateState(Messenger& _messenger, GameContext& _context,
                                   LobbyListener& _listener):
        LobbyStateRecv(_messenger, _context, _listener) {}

void LobbyCreateState::createLobby() {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    start();
}

LobbyActionQueue& LobbyCreateState::getSender() { return sender; }


void LobbyCreateState::run() {

    try {
        uint8_t id_lobby = protocol.createLobby();

        if (context.dualplay) {
            context.second_player = protocol.setdualplay(&context.first_player);
            context.id_lobby = id_lobby;

            listener.createdLobbyDual(id_lobby);
        } else {
            context.first_player = protocol.setsingleplay();
            context.second_player = 0;

            context.id_lobby = id_lobby;
            listener.createdLobbySolo(id_lobby);
        }

    } catch (const LibError& error) {
        if (protocol.isopen()) {
            std::cerr << "Lobby create lib error:" << error.what() << std::endl;
            listener.failedCreate(ERRORS[0]);
        }
        return;
    }

    LobbyActionSender actionlisten(protocol, sender);
    actionlisten.begin();

    // Open info receiver.
    listeninfo();
}
