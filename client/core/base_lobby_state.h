#ifndef BASE_LOBBY_SENDER_H
#define BASE_LOBBY_SENDER_H


#include "./lobby_listener.h"
#include "./lobby_state.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class BaseLobbyState: protected Thread, public LobbyState {
protected:
    ClientProtocol& protocol;  // cppcheck-suppress unusedStructMember
    GameContext& context;      // cppcheck-suppress unusedStructMember
    LobbyListener& listener;   // cppcheck-suppress unusedStructMember

    void listeninfo();

public:
    // Los default sin pasar por socket/protocol.
    explicit BaseLobbyState(ClientProtocol& _protocol, GameContext& _context,
                            LobbyListener& _listener);

    BaseLobbyState(BaseLobbyState&&);
    BaseLobbyState& operator=(BaseLobbyState&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    BaseLobbyState(const BaseLobbyState&) = delete;
    BaseLobbyState& operator=(const BaseLobbyState&) = delete;

    // Lobby state
    bool endstate() override;

    virtual ~BaseLobbyState();
};

#endif
