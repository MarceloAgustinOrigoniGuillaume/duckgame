#ifndef LIB_PlayerProtocol_H
#define LIB_PlayerProtocol_H

#define BUFF_LEN_CLIENT 128
#include <string>
#include <utility>
#include <atomic>

#include "common/event.h"
#include "common/dtos.h"
#include "common/protocol.h"
#include "./matchaction.h"

// Extension del protocolo base a usar.
class PlayerProtocol {

protected:
    Protocol protocol;  // Composicion con el protocolo base para la conexion
    
    std::atomic<bool> isactive; // Simple manejo de si ya se cerro o no.    

public:
    // El default a partir de socket, te ahorras el move.
    explicit PlayerProtocol(Socket&& connection);

    // Permitamos el mov para mayor flexibilidad
    explicit PlayerProtocol(Protocol&& prot): protocol(std::move(prot)) {}

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    PlayerProtocol(const PlayerProtocol&) = delete;
    PlayerProtocol& operator=(const PlayerProtocol&) = delete;

    PlayerProtocol(PlayerProtocol&&) = delete;
    PlayerProtocol& operator=(PlayerProtocol&&) = delete;

    bool recvplayercount(uint8_t* count);
    lobby_info recvlobbyinfo();
    
    bool recvsignalstart();


    // Attempts to receive pickup action.
    // If failed throws either LibError or GameError.
    player_action_dto recvaction();

    void notifypickup(const std::string& player, const uint8_t box);
    void notifynewbox();
    
    
    bool isopen();
    void close();
      
};

#endif
