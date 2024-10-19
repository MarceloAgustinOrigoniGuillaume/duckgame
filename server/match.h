#ifndef LIB_MATCH_H
#define LIB_MATCH_H

#include <mutex>
#include <queue>
#include <utility>

#include "common/dtosplayer.h"
#include "common/thread.h"

#include "server/logic_server/match_queue.h"
#include "server/logic_server/match_state.h"
#include "./playercontainer.h"

class LobbyContainer;  // Se declara existe.

typedef unsigned int lobbyID;

// Clase para encapsular la logica de lopeado. De forma asincrona.
// Delega el manejo del estado, notificado de eventos y recepcion de acciones
class Match: private Thread {
private:
    lobbyID id;               // cppcheck-suppress unusedStructMember
    PlayerContainer players;  // cppcheck-suppress unusedStructMember
    MatchState state;         // cppcheck-suppress unusedStructMember
    MatchQueue actions;       // cppcheck-suppress unusedStructMember

    // Para el thread y en general el loopeado
    void run() override;

protected:
    friend class LobbyContainer;
    void addPlayer(Player* player);

    // Metodos analogos a los de thread. expuestos a friend nada mas.
    void init();

    // Libera, bien podria prescindirse y usar un destructor.
    // Pero mejor explicitar. Reemplaza el stop.. que no se quiere permitir hacerlo sin hacer el
    // resto.
    void finish();


public:
    // Se tendra composicion con un unico observer de eventos al match.
    explicit Match(lobbyID _id);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;

    Match(Match&&) = delete;
    Match& operator=(Match&&) = delete;

    bool operator==(const Match& other) const;

    lobbyID getID() const;

    // Metodos publicos.. accesibles incluso a player controllers.
    // No hay precondiciones perse. Podria no haber empezado el match.
    // Metodos delegatorios
    void notifyAction(const PlayerActionDTO& action);
    bool isrunning() const;
    ~Match();
};

#endif
