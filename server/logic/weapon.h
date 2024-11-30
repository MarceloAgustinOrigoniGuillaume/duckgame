

#ifndef WEAPON_H
#define WEAPON_H

#include "bullet.h"
#include "common/dtosplayer.h"
#include "common/dtosobject.h"
#include "shooting_direction.h"
#include "tuple.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "common/gameevents.h"
#include "grenade.h"

class Weapon {

public:
    virtual void get_weapon(TypeWeapon& type) = 0;
    virtual void get_type(TypeDynamicObject &type) = 0;
    virtual bool shoot(ShootingDirection direction,
                       std::vector <Bullet> &bullets, Tuple bullet_position,
                       PhysicalPlayer &player, bool &trigger, int id_player,
                       std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) = 0;
    virtual int get_ammo() = 0;
    virtual ~Weapon() = default;
};


#endif  // WEAPON_H
