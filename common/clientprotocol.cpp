#include "./clientprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"

ClientProtocol::ClientProtocol(Messenger& conn): protocol(conn) {}

/*
ClientProtocol::ClientProtocol(ClientProtocol&& other): protocol(std::move(other.protocol)) {}

ClientProtocol& ClientProtocol::operator=(ClientProtocol&& other) {
    if (this == &other) {
        return *this;
    }

    protocol = std::move(other.protocol);
    return *this;
}

*/

void ClientProtocol::recvlobbyinfo(lobby_info& out) {
    // Podria tirar cast error.
    out.action = (LobbyResponseType)protocol.recvbyte();
    out.data = protocol.recvbyte();
    // throw ProtocolError("Invalid lobby info action!");
}


void ClientProtocol::sendaction(PlayerActionDTO& action) {
    // std::cout << "Sending action from: " << (int)action.playerind << "= " << (int)action.type <<
    // std::endl;
    protocol.sendbytes(&action, sizeof(action));
}

lobby_info ClientProtocol::joinLobby(const uint8_t id_match) {
    uint8_t info[2] = {LobbyActionType::JOIN_LOBBY, id_match};
    protocol.sendbytes(&info, 2);
    lobby_info out;
    recvlobbyinfo(out);

    if (out.action != JOINED_LOBBY && out.action != GAME_ERROR) {
        out.action = GAME_ERROR;
        out.data = LobbyErrorType::UNKNOWN;
    }

    // Recibir true si fallo, false si fue exito.
    return out;
}
uint8_t ClientProtocol::createLobby() {
    protocol.sendbyte(LobbyActionType::CREATE_LOBBY);
    return protocol.recvbyte();
}

uint8_t ClientProtocol::setsingleplay() {
    protocol.sendbyte(1);        // Send del playercount == 1
    return protocol.recvbyte();  // id player 1
}

uint8_t ClientProtocol::setdualplay(uint8_t* player1) {

    protocol.sendbyte(2);  // Send del playercount == 2
    *player1 = protocol.recvbyte();

    return protocol.recvbyte();
}


void ClientProtocol::sendlobbyaction(const lobby_action&& action) {
    protocol.sendbyte(action.type);
}


struct MapPoint ClientProtocol::recvmap(uint8_t* background, std::vector<BlockDTO>& out) {
    coordinate_t width = protocol.recvuint();
    coordinate_t height = protocol.recvuint();

    *background = protocol.recvbyte();

    // Read blocks
    int block_count = protocol.recvuint();
    out.reserve(block_count);

    while (block_count > 0) {
        coordinate_t _x = protocol.recvuint();
        coordinate_t _y = protocol.recvuint();

        out.emplace_back(_x, _y, (BlockTexture)protocol.recvbyte());

        block_count--;
    }


    return MapPoint(width, height);
}


MatchDto ClientProtocol::recvstate() {
    // Primero recibi info general
    match_info_dto out;
    protocol.recvbytes(&out, sizeof(out));

    MatchDto res = MatchDto(out);
    // std::cerr << "-----GOT UPDATE\n" << res.parse() << std::endl;

    int playercount = (int)protocol.recvbyte();

    while (playercount > 0) {
        PlayerDTO player;

        player.id = protocol.recvuint();
        player.pos.x = protocol.recvuint();
        player.pos.y = protocol.recvuint();

        player.weapon = (TypeWeapon)protocol.recvbyte();
        player.move_action = (TypeMoveAction)protocol.recvbyte();
        player.doing_action = (TypeDoingAction)protocol.recvbyte();


        player.is_alive = protocol.recvbyte();
        player.helmet = protocol.recvbyte();
        player.chest_armor = protocol.recvbyte();
        player.aiming_up = protocol.recvbyte();

        res.players.push_back(player);
        playercount--;
    }

    int objcount = (int)protocol.recvshort();
    // std::cout << "CLIENT RECV OBJ COUNT" << objcount << std::endl;

    while (objcount > 0) {
        DynamicObjDTO obj;

        obj.pos.x = protocol.recvuint();
        obj.pos.y = protocol.recvuint();
        obj.type = (TypeDynamicObject)protocol.recvbyte();

        res.objects.push_back(obj);
        objcount--;
    }

    /*
    for (auto playerit = state.players.begin(); playerit != state.players.end();) {
        PlayerDTO player = *playerit;
        std::cerr << "-->" << (int)player.id << " at " << player.coord_x << ","
                  << player.coord_y << std::endl;
        ++playerit;
    }
    */
    return res;
}

// Manejo de si esta abierto o no.
bool ClientProtocol::isopen() { return protocol.isactive(); }

void ClientProtocol::close() { protocol.close(); }
