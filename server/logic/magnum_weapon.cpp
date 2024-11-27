
//incluyo estas librerias provisorias
#include <cstdlib>
#include <ctime>

#include "magnum_weapon.h"

MagnumWeapon::MagnumWeapon(): ammo(6){}

void MagnumWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::MAGNUM;
}

void MagnumWeapon::shoot(ShootingDirection direction,
                               std::vector <PhysicalBullet> &bullets, Tuple bullet_position, PhysicalPlayer &player){

    if (ammo > 0){
        std::srand(std::time(nullptr));
        int dispersion_index = -2 + std::rand() % 5;
        bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y));
        if (direction == ShootingDirection::UP){
            player.add_speed(0, -20);
            bullets.back().shoot_up();
            bullets.back().add_speed(dispersion_index, -dispersion_index);
        } else if (direction == ShootingDirection::LEFT){
            player.add_speed(20, 0);
            player.add_acceleration(-5, 0);
            bullets.back().shoot_left();
            bullets.back().add_speed(dispersion_index, dispersion_index);
        } else if (direction == ShootingDirection::RIGHT){
            player.add_speed(-20, 0);
            player.add_acceleration(5, 0);
            bullets.back().shoot_right();
            bullets.back().add_speed(-dispersion_index, dispersion_index);
        }
        ammo --;
    }
}

void MagnumWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::MAGNUM;
}
