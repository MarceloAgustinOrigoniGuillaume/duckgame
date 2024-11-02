#include "./lobbycontrol.h"

#include <iostream>
#include <utility>

#include "common/core/liberror.h"
#include "common/protocolerror.h"

LobbyControl::LobbyControl(LobbyContainer& _lobbies, ServerProtocol& _protocol):
        lobbies(_lobbies), protocol(_protocol) {}

Match& LobbyControl::resolveMatch(bool* isanfitrion) {
    LobbyActionType action = protocol.recvresolveinfo();
    if (action == CREATE_LOBBY) {
        *isanfitrion = true;

        Match& newlobby = lobbies.newLobby();
        std::cerr << " created lobby id: " << (int)newlobby.getID() << std::endl;
        // Send back id...
        protocol.notifyid(newlobby.getID());

        return newlobby;
    }
    *isanfitrion = false;
    Match& res = lobbies.findLobby(protocol.recvlobbyid());

    protocol.notifyinfo(LobbyResponseType::JOINED_LOBBY, res.playercount());

    return res;
}
ControlledPlayer& LobbyControl::joinPlayers(Match& match) {
    uint8_t playercount = protocol.recvplayercount();

    ControlledPlayer& player = lobbies.joinLobby(playercount, match);
    protocol.notifyid(player.getid(0));
    if (player.playercount() == 2) {
        protocol.notifyid(player.getid(1));
    }
    std::cerr << "joined " << player.toString() << " to lobby " << (int)match.getID() << std::endl;
    return player;
}


/*
// Por ahora no hay logica de configuracion que haga el joined
// Solo puede irse.
void LobbyControl::handleJoinedLobby(ControlledPlayer& player, Match& match) {


    if (match.isrunning()) {
        // se empezo.
        protocol.notifyinfo(LobbyActionType::STARTED_LOBBY, match.playercount());
    } else {
        // se cancelo.
        protocol.notifyinfo(LobbyActionType::CANCEL_LOBBY, LobbyCancelType::ANFITRION_LEFT);
    }
    return player;
}
*/


bool LobbyControl::handleAnfitrionLobby(Match& match) {  // ControlledPlayer& player,
    try {
        // And wait..
        LobbyActionType action(protocol.recvlobbyaction());

        while (action != LobbyActionType::PLAYER_READY) {
            // Handlea accion! Si hay que hacer algo. i.e obtene info en base al tipo
            std::cerr << "RECEIVED ACTION NON READY?" << std::endl;
            action = protocol.recvlobbyaction();
        }
        lobbies.startLobby(match);
        std::cerr << "Started MATCH id: " << (int)match.getID() << " WITH: " << match.playercount()
                  << std::endl;
        return false;
    } catch (const ProtocolError& error) {
        // EOF of player. No muestres nada.
        std::cerr << "CANCELED MATCH ID: " << error.what() << " " << (int)match.getID()
                  << std::endl;
        lobbies.cancelLobby(match);
        return true;
    } catch (const LibError& error) {
        if (protocol.isactive()) {  // Si debiera estar activo. Error interno del protocol.
            std::cerr << "Lobby control error:" << error.what() << std::endl;
        }
        std::cerr << "Cancel lobby?:" << error.what() << std::endl;
        lobbies.cancelLobby(match);
        return true;
    }
}
