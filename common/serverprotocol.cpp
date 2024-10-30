#include "./serverprotocol.h"

#include <iostream>
#include <string>
#include <utility>

//#include "./gameerror.h"
#include "common/protocolerror.h"


ServerProtocol::ServerProtocol(Socket& messenger): protocol(messenger), isactive(true) {}
ServerProtocol::ServerProtocol(Messenger* messenger): protocol(messenger), isactive(true) {}
ServerProtocol::ServerProtocol(Protocol&& prot): protocol(std::move(prot)), isactive(true) {}

uint8_t ServerProtocol::recvplayercount() { return protocol.recvbyte(); }

bool ServerProtocol::recvsignalstart() {
    uint8_t sign;
    return protocol.tryrecvbyte(&sign) && sign == ((uint8_t)LobbyActionType::STARTED_LOBBY);
}

bool ServerProtocol::recvlobbyinfo(lobby_info& out) {
    uint8_t sign;
    if (!protocol.tryrecvbyte(&sign)) {
        return false;
    }
    if (LobbyActionType::CREATE_LOBBY == sign) {
        out.action = CREATE_LOBBY;
        return true;
    }

    if (LobbyActionType::JOIN_LOBBY == sign) {
        out.action = JOIN_LOBBY;
        out.attached_id = protocol.recvbyte();
        return true;
    }

    throw ProtocolError("Invalid lobby info action!");
}

void ServerProtocol::notifyid(uint8_t id) { protocol.sendbyte(id); }


PlayerActionDTO ServerProtocol::recvaction() {
    PlayerActionDTO action;
    if (!protocol.tryrecvbytes(&action, sizeof(action))) {
        isactive = false;
        throw ProtocolError("Did not receive action!");
    }
    return action;
}
void ServerProtocol::sendstate(const MatchDto&& state) { sendstate(state); }

void ServerProtocol::sendstate(const MatchDto& state) {

    // Primero envia general info
    protocol.sendbytes(&state.info, sizeof(state.info));
    protocol.sendbyte(state.players.size());

    for (auto playerit = state.players.begin(); playerit != state.players.end();) {
        PlayerDTO player = *playerit;

        // std::cout << "EL PLAYER "<< player.id<< " SENDED ESTA EN STATE: " <<
        // (int)player.move_action << std::endl;
        protocol.sendbytes(&player, sizeof(player));
        ++playerit;
    }
}


bool ServerProtocol::isopen() { return isactive.load(); }

void ServerProtocol::close() {
    if (isactive.exchange(false)) {
        protocol.close();
    }
}
