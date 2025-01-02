

#include "pewpew_laser_weapon.h"
#define DMG_MULTIPLIER 1 // podria ser configurable. Por ahora no se considera especialmente util.



PewPewLaserWeapon::PewPewLaserWeapon(int base_ammo): ammo(12*base_ammo), bullet_range(35){}

void PewPewLaserWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::PEW_PEW_LASER;
}

SoundEventType PewPewLaserWeapon::shoot_sound() const{
    return PEWPEW_SHOT;
}


bool PewPewLaserWeapon::shoot(ShootingDirection direction, std::vector <Bullet> &bullets, Tuple bullet_position,
                              PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<std::unique_ptr<Throwable>> &throwables){
    trigger = false;
    if (ammo > 0){
        Bullet& bullet1 = bullets.emplace_back(bullet_position.x, bullet_position.y, bullet_range,TypeDynamicObject::LASER, id_player, DMG_MULTIPLIER);
        Bullet& bullet2 = bullets.emplace_back(bullet_position.x, bullet_position.y, bullet_range,TypeDynamicObject::LASER, id_player, DMG_MULTIPLIER);
        Bullet& bullet3 = bullets.emplace_back(bullet_position.x, bullet_position.y, bullet_range,TypeDynamicObject::LASER, id_player, DMG_MULTIPLIER);
        if (direction == ShootingDirection::UP){
            bullet3.shoot_up();
            bullet2.shoot_up();
            bullet1.shoot_up();
            bullet3.add_speed(3, 0);
            bullet2.add_speed(-3, 0);
        } else if (direction == ShootingDirection::LEFT){
            bullet3.shoot_left();
            bullet2.shoot_left();
            bullet1.shoot_left();
            bullet3.add_speed(0, 3);
            bullet2.add_speed(0, -3);
        } else if (direction == ShootingDirection::RIGHT){
            bullet3.shoot_right();
            bullet2.shoot_right();
            bullet1.shoot_right();
            bullet3.add_speed(0, 3);
            bullet2.add_speed(0, -3);
        }
        player_sounds.push_back(SoundEventType::PEWPEW_SHOT);
        ammo --;
        return true;
    }
    return false;
}

void PewPewLaserWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::PEW_PEW_LASER;
}

int PewPewLaserWeapon::get_ammo(){
    return ammo;
}

void PewPewLaserWeapon::cheat_ammo(){
    ammo = 99;
}
