#ifndef LIB_ClientProtocol_H
#define LIB_ClientProtocol_H

#define BUFF_LEN_CLIENT 128
#include <string>
#include <utility>

#include "common/core/protocol.h"
#include "common/dtos.h"

// Extension del protocolo base a usar.
class ClientProtocol {

protected:
    Protocol protocol;  // Composicion con el protocolo base para la conexion

public:
    // El default a partir de la abstraccion de socket
    explicit ClientProtocol(Messenger* connection);
    explicit ClientProtocol(Socket& connection);
    explicit ClientProtocol(Socket&& connection);

    // Permitamos el mov para mayor flexibilidad
    explicit ClientProtocol(Protocol&& prot);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = delete;
    ClientProtocol& operator=(ClientProtocol&&) = delete;

    void joinLobby(const uint8_t playercount, const uint8_t id_match);
    void createLobby(const uint8_t playercount);

    void startlobby();

    void pickup(const uint8_t indplayer, const uint8_t box);
    MatchDto recvstate();

    void close();
};

#endif