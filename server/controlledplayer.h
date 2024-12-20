#ifndef LIB_ControlledPlayer_H
#define LIB_ControlledPlayer_H

#include <string>
#include <atomic>
#include <utility>

#include "common/dtosgame.h"
#include "common/dtoslobby.h"
#include "common/queue.h"
#include "./controlid.h"

typedef Queue<lobby_info> lobby_events;
typedef Queue<MatchDto> match_snapshots;


// La entidad player es un la parte logica que el match conoce.
// Tiene su id. Y sus eventos que se les notifico.
// Ademas de eso. Se considero pertinente poner un monitor/control del estado. Si esta abierto o no.
class ControlledPlayer {

protected:
    // Manejo de ids. Y cantidad de players para la queue de mensajes.
    const ControlId id;
    const int& pos;
    std::atomic<bool> isactive;
    // For notifying actions and/or exit.
    lobby_events events;        // cppcheck-suppress unusedStructMember
    match_snapshots snapshots;  // cppcheck-suppress unusedStructMember

    // bool _is_open;  // cppcheck-suppress unusedStructMember
    MatchStatsInfo match_stats;// cppcheck-suppress unusedStructMember

public:
    explicit ControlledPlayer(const ControlId& _id, const int& pos);
    
    // Por ahora tambien nos escapamos del move.
    ControlledPlayer(ControlledPlayer&&) = delete;

    ControlledPlayer& operator=(ControlledPlayer&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    ControlledPlayer(const ControlledPlayer&) = delete;
    ControlledPlayer& operator=(const ControlledPlayer&) = delete;


    // No hace falta perse el operador se podria usar el getter de id.
    bool operator==(const ControlledPlayer& other) const;

    uint8_t playercount() const;
    
    const ControlId& getcontrolid() const;
    
    player_id getid(const uint8_t ind) const;
    
    int getpos() const;

    // Abre la queue de lobby info del jugador, cierra la de matchdto, indicando esta activo en una
    // lobby.
    bool setlobbymode(const MatchStatsInfo& match_stats);
    
    const MatchStatsInfo& getStats();
    // Abre la queue de matchdto, cierra le de lobby info. Indicando fase de juego.
    bool setgamemode(const MatchStatsInfo& match_stats);
    
    void waitgamemode();
    void waitlobbymode();


    // Desconecta/cierra el player, las queues. Y setea como cancelada las stats.
    // Para el server
    bool canceled();
    
    // Retorna false si esta inactivo. True si esta activo y cierra las queues.
    // Para los notifiers/control receivers. Que reciben del cliente
    bool trydisconnect();
    
    // recveinfo es no bloqueante! Recibe el lobby info con try_push a la queue del player
    // Todo es "bloqueante" por posibles locks... pero bueno
    bool recvinfo(const lobby_info& dto);

    // Pop lobby info. Bloqueante. Si no hay eventos espera a uno.
    lobby_info popinfo();

    // recvevent es no bloqueante! Recibe el evento con try_push a la queue del player
    // Todo es "bloqueante" por posibles locks... pero bueno
    bool recvstate(const MatchDto& dto);

    // Pop event. Bloqueante. Si no hay eventos espera a uno.
    MatchDto popstate();


    std::string toString();
    //~ControlledPlayer();
};

#endif
