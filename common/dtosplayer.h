#ifndef LIB_DTOS_PLAYER_H
#define LIB_DTOS_PLAYER_H

#include <cstdint>
#include <vector>
#include "./dtosobject.h"
#include "./gameevents.h"

typedef unsigned int player_id;


enum PlayerActionType : uint8_t {
    NONE = 0,
    MOVE_LEFT = 1,
    MOVE_LEFT_END = 2,
    MOVE_RIGHT = 3,
    MOVE_RIGHT_END = 4,
    STAY_DOWN = 5,
    JUMP = 6,
    FLAPPING_END = 7,
    STAY_DOWN_START = 8,
    STAY_DOWN_END = 9,
    AIM_UP_START = 10,
    AIM_UP_END = 11,
    SHOOT_START = 12,
    SHOOT_END = 13,
    PICK_UP_DROP_ITEM = 14,

    CHEAT_1 = 15,
    CHEAT_2 = 16,
    CHEAT_3 = 17,
    
    FORCE_CANCEL_MATCH = 19,
    TOGGLE_DBG_MODE = 20,
    EQUIP_ARMOR = 21,
    EQUIP_HELMET = 22,
    EQUIP_GRENADE = 23,
    EQUIP_BANANA = 24,
    EQUIP_PEWPEW = 25,
    EQUIP_LASER = 26, 
    EQUIP_AK47 = 27, 
    EQUIP_DUEL_PISTOL = 28, 
    EQUIP_COWBOY = 29, 
    EQUIP_MAGNUM = 30,
    EQUIP_SHOTGUN = 31, 
    EQUIP_SNIPER = 32, 
    RELOAD = 33,
    
};

struct PlayerActionDTO {
    PlayerActionType type;
    uint8_t playerind;
    //uint8_t specific_info;

    PlayerActionDTO(const PlayerActionType& _type, uint8_t _playerind):
            type(_type), playerind(_playerind){}//, specific_info(0) {}
    //PlayerActionDTO(const PlayerActionType& _type, uint8_t _playerind, uint8_t _info):
    //        type(_type), playerind(_playerind){}//, specific_info(_info) {}
    PlayerActionDTO(): type(NONE), playerind(0){}//, specific_info(0) {}
} __attribute__((packed));


enum class TypeWeapon : uint8_t {
    NONE,
    GRANADA,
    BANANA,
    PEW_PEW_LASER,
    LASER_RIFLE,
    AK_47,
    PISTOLA_DE_DUELOS,
    PISTOLA_COWBOY,
    MAGNUM,
    ESCOPETA,
    SNIPER
};

enum class TypeMoveAction : uint8_t {
    NONE,
    MOVE_LEFT,
    MOVE_RIGHT,
    STAY_DOWN,
    AIR_NEUTRAL,
    AIR_LEFT,
    AIR_RIGHT,
    FLAP_NEUTRAL,
    FLAP_LEFT,
    FLAP_RIGHT
};

enum class TypeDoingAction : uint8_t {
    NONE,
    SHOOTING,
    SHOOTING_UP,
    DAMAGED,
    PICK_UP,
    RELOADING,
};  // Capaz podria estar aca el flapping?

struct PlayerDTO {
    int id;
    struct MapPoint pos;
    bool is_alive;
    
    TypeWeapon weapon;
    
    TypeMoveAction move_action;
    TypeDoingAction doing_action;

    bool helmet;
    bool chest_armor;
    bool aiming_up;

    int hp;
    int munition;

    PlayerDTO(int id_, bool alive, int x, int y, TypeWeapon w, bool h, bool armor,
              TypeMoveAction action):
            id(id_),
            pos(x, y),
            is_alive(alive),
            weapon(w),
            move_action(action),
            doing_action(TypeDoingAction::NONE),
            helmet(h),
            chest_armor(armor),
            aiming_up(false),
            hp(0),
            munition(0)
            {}

    PlayerDTO(int id_, bool alive, int x, int y, TypeMoveAction state):
            id(id_),
            pos(x, y),
            is_alive(alive),
            weapon(TypeWeapon::NONE),
            move_action(state),
            doing_action(TypeDoingAction::NONE),
            helmet(false),
            chest_armor(false),
            aiming_up(false),
            hp(alive?1:0),
            munition(0)
            {}
    PlayerDTO(): PlayerDTO(0, false, 0, 0, TypeMoveAction::NONE) {}
};

#endif
