#include "./lobbycontrol.h"

#include <iostream>
#include <utility>

#include "common/protocolerror.h"

LobbyControl::LobbyControl(LobbyContainer& _lobbies, ServerProtocol& _protocol):
        lobbies(_lobbies), protocol(_protocol) {}

Match& LobbyControl::resolveMatch(bool* isanfitrion) {
    lobby_info info;
    if (!protocol.recvlobbyinfo(info)) {
        throw ProtocolError("Client aborted before sending lobby info");
    }

    if (info.action == CREATE_LOBBY) {
        *isanfitrion = true;

        Match& newlobby = lobbies.newLobby();
        std::cerr << " created lobby id: " << (int)newlobby.getID() << std::endl;
        // Send back id...
        protocol.notifyid(newlobby.getID());

        return newlobby;
    }
    *isanfitrion = false;
    std::cerr << " JOIN lobby id: " << (int)info.attached_id << std::endl;
    Match& res = lobbies.findLobby(info.attached_id);

    protocol.notifyaction(LobbyActionType::JOIN_LOBBY);

    return res;
}

ControlledPlayer& LobbyControl::waitStart(Match& match) {
    uint8_t playercount = protocol.recvplayercount();

    ControlledPlayer& player = lobbies.joinLobby(playercount, match);
    protocol.notifyid(player.getid(0));
    if (player.playercount() == 2) {
        protocol.notifyid(player.getid(1));
    }

    std::cerr << "joined " << player.toString() << " to lobby " << (int)match.getID() << std::endl;

    player.open();

    match.waitStart();
    if (match.isrunning()) {
        // se empezo.
        protocol.notifyinfo(LobbyActionType::STARTED_LOBBY, match.playercount());
    } else {
        // se cancelo.
        protocol.notifyinfo(LobbyActionType::CANCEL_LOBBY, LobbyCancelType::ANFITRION_LEFT);
    }

    return player;
}
ControlledPlayer& LobbyControl::start(Match& match) {
    uint8_t playercount = protocol.recvplayercount();

    ControlledPlayer& player = lobbies.joinLobby(playercount, match);
    protocol.notifyid(player.getid(0));
    if (player.playercount() == 2) {
        protocol.notifyid(player.getid(1));
    }

    std::cerr << "joined " << player.toString() << " anfitrion of lobby " << (int)match.getID()
              << std::endl;


    // And wait..
    if (!protocol.recvsignalstart()) {
        throw ProtocolError("Did not receive new lobby start match signal");
    }

    player.open();
    lobbies.startLobby(match);
    std::cerr << "Started MATCH id: " << (int)match.getID() << "WITH: " << match.playercount()
              << std::endl;

    protocol.notifyinfo(LobbyActionType::STARTED_LOBBY, match.playercount());

    return player;
}
