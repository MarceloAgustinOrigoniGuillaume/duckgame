#ifndef LIB_DTOS_H
#define LIB_DTOS_H

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "./dtosobject.h"
#include "./dtosplayer.h"

enum LobbyCancelType : uint8_t { UNKNOWN = 0, ANFITRION_LEFT = 1, GAME_ERROR = 2 };

enum LobbyActionType : uint8_t {
    // Tipos acciones para unirse/salir ademas
    CREATE_LOBBY = 0x16,
    JOIN_LOBBY = 0x17,
    LEAVE_LOBBY = 0x20,
    // Para empezar/cancelar
    STARTED_LOBBY = 0x18,
    CANCEL_LOBBY = 0x19
    // Tipos de acciones de configuracion?
};

struct lobby_info {
    LobbyActionType action;
    uint8_t attached_id;  // Un numero. Que muchas veces es necesario

    lobby_info(LobbyActionType _action, uint8_t num): action(_action), attached_id(num) {}
    lobby_info(): action(CANCEL_LOBBY), attached_id(0) {}
} __attribute__((packed));

struct lobby_action {
    LobbyActionType type;
    uint8_t info;  // Podria ser el del lobby o uno para seleccionar el mapa.
} __attribute__((packed));


enum MatchStateType : uint8_t {
    INICIADA = 0x01,
    TERMINADA = 0x02,
    CANCELADA = 0x03,
};

struct match_info_dto {
    MatchStateType estado;
    uint8_t numronda;
    // uint8_t cantidadjugadores;
};

class MatchDto {
public:
    match_info_dto info;
    std::vector<PlayerDTO> players;      // cppcheck-suppress unusedStructMember
    std::vector<DynamicObjDTO> objects;  // cppcheck-suppress unusedStructMember

    explicit MatchDto(MatchStateType _estado, uint8_t _numronda): info({_estado, _numronda}) {}
    explicit MatchDto(match_info_dto _info): info(_info) {}
    MatchDto(): info({INICIADA, 0}) {}


    std::string parse() const {
        std::stringstream result;
        if (info.estado == INICIADA) {
            result << "INICIADA ";
        } else if (info.estado == TERMINADA) {
            result << "TERMINADA ";

        } else if (info.estado == CANCELADA) {
            result << "CANCELADA ";
        }
        result << (int)info.numronda;
        return result.str();
    }
};

struct PlayerStatDto {
    uint8_t id;    // cppcheck-suppress unusedStructMember
    uint8_t wins;  // cppcheck-suppress unusedStructMember
};

// Info estadisticas
class StatInfoDto {
public:
    MatchStateType estado;
    uint8_t numronda;
    std::vector<PlayerStatDto> stats;  // cppcheck-suppress unusedStructMember

    explicit StatInfoDto(MatchStateType _estado, uint8_t _numronda):
            estado(_estado), numronda(_numronda) {}
};


#endif
