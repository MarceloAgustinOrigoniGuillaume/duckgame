

#include "spawn_place.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

SpawnPlace::SpawnPlace(int position_x_, int position_y_,
           int range_x, int range_y, int time_respawn, float time_sleep):
            possible_weapon(nullptr), spawn_point{position_x_, position_y_},
            dimension{range_x, range_y}, time_respawn(time_respawn), spawned(true), time_sleep(time_sleep),
            timer(this->time_respawn * this->time_sleep){

            }

void SpawnPlace::spawn_item() {
    // TODO refactorizar este switch
    if (possible_weapon != nullptr) {
        return;
    }
    std::cout<<"Spawn Item"<<std::endl;
    std::srand(std::time(nullptr));
    int random_weapon = 0 + std::rand() % 4;
    switch (random_weapon){
        case 0:
            possible_weapon = std::make_unique<CowboyPistolWeapon>();
            std::cout<<"Spawn Cowboypistol"<<std::endl;
            //item = TypeDynamicObject::PISTOLA_COWBOY;
            spawned = true;
            break;
        case 1:
            possible_weapon = std::make_unique<MagnumWeapon>();
            std::cout<<"Spawn Magnum"<<std::endl;
            //item = TypeDynamicObject::MAGNUM;
            //item = TypeDynamicObject::PISTOLA_COWBOY;
            spawned = true;
            break;
        case 2:
            possible_weapon = std::make_unique<DuelPistol>();
            std::cout<<"spawn duel pistol"<<std::endl;
            //item = TypeDynamicObject::PISTOLA_DE_DUELOS;
            //item = TypeDynamicObject::PISTOLA_COWBOY;
            spawned = true;
            break;
        case 3:
            possible_weapon = std::make_unique<PewPewLaserWeapon>();
            std::cout<<"spawn pew pew laser"<<std::endl;
            //item = TypeDynamicObject::PEW_PEW_LASER;
            //item = TypeDynamicObject::PISTOLA_COWBOY;
            spawned = true;
            break;
        default:
            possible_weapon = std::make_unique<CowboyPistolWeapon>();
            std::cout<<"Spawn Cowboypistol"<<std::endl;
            //item = TypeDynamicObject::PISTOLA_COWBOY;
            spawned = true;
            break;
    }

}

std::unique_ptr<Weapon> SpawnPlace::get_weapon(){
    if (spawned){
        spawned = false;
        //TODO cambiar el timer
        timer = 200;
        auto weapon = std::move(possible_weapon);
        possible_weapon = nullptr;
        return weapon;
    }
    return nullptr;
}

Tuple SpawnPlace::get_spawn_point() {
    return spawn_point;
}

Tuple SpawnPlace::get_dimension() {
    return dimension;
}

bool SpawnPlace::is_spawned() {
    return spawned;
}



void SpawnPlace::pass_time(){
    if (!spawned && time_respawn > 0) {
        timer--;
        //std::cout << "TIMER SPAWNER: "<< timer <<std::endl;
        if (timer <= 0) {
            this->spawn_item();
        }
    }

}

void SpawnPlace::take_item(TypeDynamicObject &item_) {
    item_ = this->item;
    spawned = false;
    timer = this->time_respawn / this->time_sleep;
}

void SpawnPlace::get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_) {
    position_x_ = this->spawn_point.x;
    position_y_ = this->spawn_point.y + 10;
    if (possible_weapon != nullptr){
        possible_weapon->get_type(object_);
    }
}

bool SpawnPlace::is_on_range(int player_position_x, int player_position_y){
    return (player_position_x >= spawn_point.x - 8 && player_position_x <= spawn_point.x + dimension.x  + 8&&
                player_position_y >= spawn_point.y && player_position_y <= spawn_point.x + dimension.y);
}


TypeDynamicObject SpawnPlace::get_item(){
    return item;
}