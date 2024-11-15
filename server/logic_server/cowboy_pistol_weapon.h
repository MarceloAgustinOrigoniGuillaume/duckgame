
#ifndef COWBOY_PISTOL_WEAPON_H
#define COWBOY_PISTOL_WEAPON_H

#include "weapon.h"
#include "tuple.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"

class CowboyPistolWeapon: public Weapon{

    private:
        int ammo;

    public:
        CowboyPistolWeapon();
        void get_weapon(TypeWeapon& type) override;
        void shoot(ShootingDirection direction,
                   std::vector<PhysicalBullet> &bullets, Tuple bullet_position) override;

};

#endif //COWBOY_PISTOL_WEAPON_H