#include "./lobby_client_sender.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/protocolerror.h"

#define ASK_NAME "What is your name?"
#define ACTION_EXIT "Exit"
#define ACTION_PICKUP "Pickup"
#define ACTION_READ "Read"


LobbyClientSender::LobbyClientSender(ClientProtocol& _protocol, GameContext& _context):
        protocol(&_protocol), mode(NULL), context(_context) {}

LobbyClientSender::LobbyClientSender(LobbyClientSender&& other):
        protocol(other.protocol), mode(NULL), context(other.context) {
    other.protocol = NULL;
    std::cout << "MOVED CLIENT SENDER OWN " << protocol << std::endl;
}
LobbyClientSender& LobbyClientSender::operator=(LobbyClientSender&& other) {
    if (protocol == other.protocol) {
        return *this;
    }

    this->protocol = other.protocol;
    this->mode = other.mode;
    this->context = other.context;
    other.protocol = NULL;

    return *this;
}

void LobbyClientSender::cancel() {}
void LobbyClientSender::doaction(const lobby_action& action) {
    std::cout << "SEND ACTION? " << &action << std::endl;
}

void LobbyClientSender::handleJoin() {
    std::cerr << "lobby id to join: " << (int)context.id_lobby << std::endl;
    protocol->joinLobby(context.id_lobby);

    if (context.dualplay) {
        context.second_player = protocol->setdualplay(&context.first_player);
    } else {
        context.first_player = protocol->setsingleplay();
        context.second_player = 0;
    }
}

void LobbyClientSender::handleCreate() {
    uint8_t id_lobby = protocol->createLobby();

    if (context.dualplay) {
        context.second_player = protocol->setdualplay(&context.first_player);
    } else {
        context.first_player = protocol->setsingleplay();
        context.second_player = 0;
    }

    std::cerr << "press enter to start the match! lobby id: " << (int)id_lobby << std::endl;

    std::string action;
    if (!(std::cin >> action)) {  // Could not read if new lobby.
        throw ProtocolError("Did not read match start!!");
    }

    protocol->startlobby();
}

void LobbyClientSender::createLobby(bool dualplay) {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    context.dualplay = dualplay;
    mode = &LobbyClientSender::handleCreate;
    start();
}

void LobbyClientSender::joinLobby(bool dualplay, unsigned int idlobby) {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }

    context.dualplay = dualplay;

    context.id_lobby = idlobby;
    mode = &LobbyClientSender::handleJoin;
    start();
}


bool LobbyClientSender::isrunning() { return _is_alive; }
void LobbyClientSender::run() {
    (this->*mode)();  // exec lobby mode.
}


int LobbyClientSender::getcount() {
    std::cout << ASK_NAME << std::endl;

    std::string name;
    if (!(std::getline(std::cin, name, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read player name");
    }

    std::string name2;

    std::cerr << ASK_NAME << " segundo player" << std::endl;
    if (!(std::getline(std::cin, name2, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read second player name");
    }

    if (name2.size() > 0) {
        std::cerr << "2 players: " << name << " " << name2 << std::endl;
        return 2;
    }
    std::cerr << "1 player: " << name << std::endl;
    return 1;
}


LobbyClientSender::~LobbyClientSender() {
    if (_keep_running) {
        stop();
        join();
    }
}
