#ifndef LIB_MATCH_H
#define LIB_MATCH_H

#include <condition_variable>
#include <mutex>
#include <optional>
#include <vector>
#include <queue>
#include <utility>

#include "common/dtosplayer.h"
#include "common/queue.h"
#include "common/thread.h"
#include "serial/map_loader.h"

// Descomentar si ya son usables.
#include "server/core/match_state.h"
#include "server/core/configuration.h"

// Logica sencilla del tp de threads
#include "./playercontainer.h"

//#include "server/simple_logic/simpleloop.h"
//#include "server/simple_logic/simplequeue.h"

class LobbyContainer;  // Se declara existe.

typedef unsigned int lobbyID;

// Clase para encapsular la logica de lopeado. De forma asincrona.
// Delega el manejo del estado, notificado de eventos y recepcion de acciones
class Match: private Thread {
private:
    typedef void (Match::* round_resetter)();
    
    lobbyID id;               // cppcheck-suppress unusedStructMember
    PlayerContainer players;  // cppcheck-suppress unusedStructMember
    MatchState looper;        // cppcheck-suppress unusedStructMember
    int connectedplayers;     // cppcheck-suppress unusedStructMember
    MapLoader& maps; // cppcheck-suppress unusedStructMember
    round_resetter reset_round;// cppcheck-suppress unusedStructMember
    
    // Para el cliente
    MapInfo map;              // cppcheck-suppress unusedStructMember
    MatchStatsInfo stats;// cppcheck-suppress unusedStructMember
    
    
    
    // Para el server
    struct ObjectsInfo objects;// cppcheck-suppress unusedStructMember

    // Para el thread y en general el loopeado
    void run() override;
    
    
    void resetFixedMap();
    void resetRandomMap();

protected:
    friend class LobbyContainer;
    
    //Returns ids on out.
    void addPlayers(ControlId& out);
    ControlledPlayer& getPlayer(const ControlId& id);

    bool notifyDisconnect(ControlledPlayer& player);
    void hostLobbyLeft(ControlledPlayer& host);

    // Metodos analogos a los de thread. expuestos a friend nada mas.
    void init(const char* mapname);
    void cancelByError(LobbyErrorType error);

    // Libera, bien podria prescindirse y usar un destructor.
    // Pero mejor explicitar. Reemplaza el stop.. que no se quiere permitir hacerlo sin hacer el
    // resto.
    void finish();
    
    bool pauseMatch(int count_seconds);
    //bool roundEnded();
    void loadMap(MapDeserializer& deserial);
    bool handlePostRound();
public:
    explicit Match(lobbyID _id, const int max_players, const Configuration& configs, MapLoader& _maps);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;

    Match(Match&&) = delete;
    Match& operator=(Match&&) = delete;

    bool operator==(const Match& other) const;

    lobbyID getID() const;
    const MapInfo& getMap() const;
    const MatchStatsInfo& getStats() const;
    // void waitStart();
    int playercount() const;
    void putPlayers(std::vector<player_id>& out) const;

    // Metodos publicos.. accesibles incluso a player controllers.
    // No hay precondiciones perse. Podria no haber empezado el match.
    // Metodos delegatorios
    void notifyAction(const PlayerActionDTO& action);
    bool isrunning() const;
    bool canaddplayer() const;
    ~Match();
};

#endif
