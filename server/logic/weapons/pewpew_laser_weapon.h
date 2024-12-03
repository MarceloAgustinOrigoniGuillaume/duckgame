

#ifndef PEWPEW_LASER_WEAPON_H
#define PEWPEW_LASER_WEAPON_H

#include "bullet.h"
#include "weapon.h"
#include "common/dtosplayer.h"
#include "server/logic/weapons/shooting_direction.h"
#include "server/logic/physical/physical_bullet.h"
#include "server/logic/physical/physical_player.h"
#include "common/gameevents.h"
#include "grenade.h"
#include "throwable.h"
#include <memory>

class PewPewLaserWeapon : public Weapon {

    private:
        int ammo;
        int bullet_range;

    public:
        PewPewLaserWeapon(int base_ammo);
        SoundEventType shoot_sound() const override;                
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction, std::vector<Bullet> &bullets,
                   Tuple bullet_position, PhysicalPlayer &player, bool &trigger,
                   int id_player, std::vector<SoundEventType> &player_sounds, std::vector<std::unique_ptr<Throwable>> &throwables) override;
        int get_ammo() override;
        void cheat_ammo() override;
};


#endif //PEWPEW_LASER_WEAPON_H