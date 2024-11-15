

#include "cowboy_pistol_weapon.h"

CowboyPistolWeapon::CowboyPistolWeapon(): ammo(6){}

void CowboyPistolWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::PISTOLA_COWBOY;
}

void CowboyPistolWeapon::shoot(ShootingDirection direction,
                               std::vector <PhysicalBullet> &bullets, Tuple bullet_position){
    if (ammo > 0){
        bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y));
        if (direction == ShootingDirection::UP){
            bullets.back().shoot_up();
        } else if (direction == ShootingDirection::LEFT){
            bullets.back().shoot_left();
        } else if (direction == ShootingDirection::RIGHT){
            bullets.back().shoot_right();
        }
        ammo --;
    }

}