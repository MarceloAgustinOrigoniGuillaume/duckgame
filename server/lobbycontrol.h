#ifndef LIB_LobbyControl_H
#define LIB_LobbyControl_H


#include "./controlledplayer.h"
#include "./lobbycontainer.h"
#include "./match.h"
#include "common/serverprotocol.h"

class LobbyControl {
protected:
    LobbyContainer& lobbies;   // cppcheck-suppress unusedStructMember
    ServerProtocol& protocol;  // cppcheck-suppress unusedStructMember
public:
    // Crea el player con el ide pasado e inicia el protocolo
    explicit LobbyControl(LobbyContainer& _lobbies, ServerProtocol& _protocol);

    // Por ahora tambien nos escapamos del move.
    LobbyControl(LobbyControl&&) = delete;
    LobbyControl& operator=(LobbyControl&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    LobbyControl(const LobbyControl&) = delete;
    LobbyControl& operator=(const LobbyControl&) = delete;

    Match& resolveMatch(bool* isanfitrion);

    ControlledPlayer& start(Match& match);
    ControlledPlayer& waitStart(Match& match);
};

#endif