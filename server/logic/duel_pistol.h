
#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "bullet.h"
#include "common/gameevents.h"

class DuelPistol : public Weapon{

    private:
        int ammo;
        int bullet_range;

    public:
        DuelPistol();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction, std::vector<Bullet> &bullets, Tuple bullet_position,
                   PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds) override;
        int get_ammo() override;
};



#endif //DUEL_PISTOL_H
