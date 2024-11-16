#include "./match.h"

#include <iostream>

#define MS_SECOND 1000
#define PAUSE_SECONDS 3

#include "./gameerror.h"
//#include <thread>
#include "common/clock.h"

Match::Match(lobbyID _id): id(_id), players(), looper(), connectedplayers(0), map() {}


// Protected// friend accessed methods
ControlledPlayer& Match::addPlayers(uint8_t count) {
    ControlledPlayer& player = players.add(count);

    // Se suma despues porque el add puede fallar!
    // Por capacidad o por que esta cancelada!
    connectedplayers++;  // Solo importa la cantidad de conectados...


    return player;
}
int Match::playercount() const { return players.playercount(); }


bool Match::notifyDisconnect(ControlledPlayer& player) {
    connectedplayers--;  // Solo importa la cantidad de conectados
    if (player.disconnect()) {
        // Si se esta desconectando ahora entonces notifica.
        std::cout << "Disconnected player from match? now " << connectedplayers << std::endl;
        if (_keep_running) {
            return connectedplayers == 0;
        }

        players.remove(player);
    }
    return connectedplayers == 0;
}

void Match::init(MapLoader& maps, const char* mapname) {
    if (is_alive()) {
        throw GameError(LOBBY_ALREADY_STARTED, "Tried to start a match already started!!\n");
    }    
    
    MapDeserializer& deserial = maps.getLoader(mapname);

    deserial.loadMapInfo(map);

    // Notify/start players. Ya podrian enviar la info del mapa.
    looper.start_players(players, stats);
    players.finishLobbyMode();

    // Carga info para el server
    objects = ObjectsInfo(map.size.x,map.size.y);

    deserial.loadObjectsInfo(objects);

    // Se podria hacer un merge de bloques! A la forma greedy
    objects.blocks.reserve(map.blocks.size());
    for (const struct BlockDTO& block: map.blocks) {
        objects.blocks.emplace_back(block.pos.x, block.pos.y);
    }

    looper.add_objects(objects);

    start();
    // match_start.notify_all();
}

bool Match::hostLobbyLeft(ControlledPlayer& host) {
    connectedplayers--;
    if (connectedplayers == 0) {
        host.disconnect();
        return true;
    }
    // Notifica a los otros ademas del disconnect.
    host.disconnect();
    players.hostLobbyLeft(host);

    return false;
}

void Match::cancelByError(LobbyErrorType error) { players.cancelByError(error); }


// General/public methods.

bool Match::operator==(const Match& other) const { return this->id == other.id; }


lobbyID Match::getID() const { return this->id; }

// Metodos delegatorios.
void Match::notifyAction(const PlayerActionDTO& action) {
    if (stats.state == INICIADA) {
        looper.pushAction(action);
    }
}

const MatchStatsInfo& Match::getStats() const{
     return this->stats;
}

bool Match::pausedMatch(){
    Clock timer(MS_SECOND);  // Timer de a pasos de 1 segundo.
    timer.resetnext();
    int mx = PAUSE_SECONDS;

    lobby_info info(MATCH_PAUSE_TICK, mx);

    while (_keep_running && timer.tickcount() < mx) {
        info.data = mx - timer.tickcount();
        players.notifyInfo(info);
        timer.tickRest();  // sleep for 1 second if so is needed
    }
    
    //timer.tickcount() >= mx
    // No se envia si se cancelo con la 'q' en el medio. Se handlea despues?
    if (_keep_running) { 
        info.action = MATCH_PAUSE_END;
        info.data = 0;  // reset data

        players.notifyInfo(info);
        return true;
    }
    
    return false;
}

bool Match::handlePostRound(){
    if(this->stats.isRunning()){
        //std::cout << "HANDLE POST ROUND ON MATCH!\n";
        players.finishGameMode(this->stats);  // Notify/move players to lobby mode.
        bool handled = true;
        if(this->stats.isPaused()){
             handled = pausedMatch();
        }
        // Go back to game mode.. independientemente de si cancelo o no.
        players.finishLobbyMode(); 
        //std::cout << "FINISHED HANDLE POST ROUND ON MATCH!\n";
        return handled;
    }
    
    return false;
}

void Match::run() {

    looper.playRound(players, this->stats);
    while (_keep_running && handlePostRound()) {
        //looper.start_players(players, stats);
        // re envia info del mapa?
        
        looper.playRound(players, this->stats);
    }

    if (this->stats.isRunning()) {
        std::cout << "NOT FINISHED? FORCE CANCEL!\n";
        this->stats.state = CANCELADA;
    } else{
        std::cout << "FINISHED MATCH? NOTIFY!!! "<< stats.parse()<<" \n";    
    }
    players.finishGameMode(this->stats);

    // Checkea si el finish fue natural o forzado.

    // notifica los playeres. Del final.
    players.forceDisconnectAll();
}

bool Match::isrunning() const { return stats.isRunning(); }

const MapInfo& Match::getMap() const { return map; }


void Match::finish(MapLoader& maps) {
    maps.removeLoader(map.map_id);

    if (_keep_running) {
        stop();
        looper.stop();
        join();
        return;
    }
    // El finish en caso de no estar corriendo.
    // Asume que se esta en lobby mode.
    players.forceDisconnectAll();
}

Match::~Match() {
    if (_keep_running) {
        stop();
        looper.stop();
        join();
    }
}
