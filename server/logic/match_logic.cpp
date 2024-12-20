#include "match_logic.h"

#include <iostream>


MatchLogic::MatchLogic(const Configuration& _configs): colition_map(100, 100), configs(_configs) {
    this->command_map[PlayerActionType::NONE] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };
    this->command_map[PlayerActionType::MOVE_LEFT] = [this](int index) {
        this->change_player_dir(index, MOVING_LEFT); // Para que se mueva left
    };
    this->command_map[PlayerActionType::MOVE_LEFT_END] = [this](int index) {
        this->still_player(index, MOVING_LEFT);
    };

    this->command_map[PlayerActionType::MOVE_RIGHT] = [this](int index) {
        this->change_player_dir(index, MOVING_RIGHT); // Para que se mueva a la derecha
    };
    this->command_map[PlayerActionType::MOVE_RIGHT_END] = [this](int index) {
        this->still_player(index,MOVING_RIGHT);
    };

    this->command_map[PlayerActionType::JUMP] = [this](int index) {
        this->player_jump_start(index);
    };

    this->command_map[PlayerActionType::FLAPPING_END] = [this](int index) {
        this->player_jump_end(index);
    };

    this->command_map[PlayerActionType::STAY_DOWN_START] = [this](int index) {
        this->player_stay_down_start(index);
    };
    this->command_map[PlayerActionType::STAY_DOWN_END] = [this](int index) {
        this->player_stay_down_end(index);
    };

    this->command_map[PlayerActionType::AIM_UP_START] = [this](int index) {
        this->player_aim_up_start(index);
    };
    this->command_map[PlayerActionType::AIM_UP_END] = [this](int index) {
        this->player_aim_up_end(index);
    };
    this->command_map[PlayerActionType::SHOOT_START] = [this](int index) {
        this->player_shoot(index);
    };

    this->command_map[PlayerActionType::SHOOT_END] = [this](int index) {
        this->player_shoot_end(index);
    };

    this->command_map[PlayerActionType::PICK_UP_DROP_ITEM] = [this](int index) {
        this->player_toggle_pick_up_drop_item(index);
    };

    this->command_map[PlayerActionType::CHEAT_1] = [this](int index) {
        this->player_cheat_1();
    };

    this->command_map[PlayerActionType::CHEAT_2] = [this](int index) {
        this->player_cheat_2();
    };

    this->command_map[PlayerActionType::CHEAT_3] = [this](int index) {
        this->player_cheat_3();
    };

}



void MatchLogic::add_player(int id, int spawn_point_index) {
    //std::cout << "player SPAWN POINT INDEX: "<< spawn_point_index << std::endl;
    //std::cout << "player SPAWN POINT pos: " << spawn_points[spawn_point_index].x*16
    //<<", "<< spawn_points[spawn_point_index].y*16
    //<< std::endl;

    if (spawn_point_index < spawn_points.size()) {
        players.push_back(Player(id, spawn_points[spawn_point_index].x  * 16, spawn_points[spawn_point_index].y  * 16 + 1, configs));
        std::cout << "spawn point x: " << spawn_points[spawn_point_index].x << ", y: " << spawn_points[spawn_point_index].y << std::endl;
    } else {
        players.push_back(Player(id, 10 + 50 * id, 1, configs));
    }
    colition_map.add_collision(players.back().get_map_position(), players.back().get_dimension(),
                               CollisionTypeMap::PLAYER, players.back().get_id());
}


void MatchLogic::change_player_dir(int id, PlayerMovingDir dir){
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.change_move_dir(dir);
            return;
        }
    }
}

void MatchLogic::add_player_speed(int id, int speed_x, int speed_y) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.add_speed(speed_x, speed_y);
            return;
        }
    }
}

void MatchLogic::player_shoot(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.shoot_start();
            return;
        }
    }
}

void MatchLogic::player_shoot_end(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.shoot_end();
            return;
        }
    }
}

void MatchLogic::player_jump_start(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.jump_start();
            return;
        }
    }
}

void MatchLogic::player_jump_end(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.jump_end();
            return;
        }
    }
}

void MatchLogic::player_toggle_pick_up_drop_item(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {

            if(player.pick_up_item(this->spawn_places, this->dropped_items)){
                return;
            }

            if (player.has_equipment()) {
                player.drop_item(this->dropped_items);
            }
            return;
        }
    }
}

void MatchLogic::player_aim_up_start(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.aim_up_start();
            return;
        }
    }
}

void MatchLogic::player_aim_up_end(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.aim_up_end();
            return;
        }
    }
}

void MatchLogic::player_stay_down_start(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.stay_down_start();
            return;
        }
    }
}

void MatchLogic::player_stay_down_end(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.stay_down_end();
            return;
        }
    }
}

void MatchLogic::still_player(int id, PlayerMovingDir dir) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.undo_moving(dir);
            return;
        }
    }
}

void MatchLogic::update_players(std::vector<int> &id_alive_players) {
    id_alive_players.clear();
    for (Player& player: players) {
        player.update(colition_map, bullets, throwables);
        if (player.is_still_alive()){
            id_alive_players.push_back(player.get_id());
        }
    }
}

void MatchLogic::update_colition_map() {
    colition_map.clear_map();
    for (Player& player: players) {
        colition_map.add_collision(player.get_map_position(), player.get_dimension(), CollisionTypeMap::PLAYER, player.get_id());
    }
    for (Box& box: boxes) {
        if (box.is_spawned()){

            colition_map.add_collision(box.get_spawn_point(), box.get_dimension(), CollisionTypeMap::BOX, box.get_id());
        }
    }

    int block_index = 0;
    for (MapPoint& block: blocks) {
        Tuple position = {block.x, block.y};
        Tuple dimension = {16, 16};
        colition_map.add_collision(position, dimension, CollisionTypeMap::BLOCK, block_index);
        block_index ++;
    }

    /*
    int banana_index = 0;
    for (MapPoint& banana: bananas){
        Tuple position = {banana.x, banana.y};
        Tuple dimension = {10, 5};
        colition_map.add_collision(position, dimension, CollisionTypeMap::BANANA, banana_index);
        banana_index ++;
    }
    
    */

}

/*void MatchLogic::add_colition(PhysicalObject &object) {

    //colition_map.add_colition(object);

    //colition_map.add_temp_collision(position.x + dimension.x, position.y + dimension.y);

    // for (int i = 0; i < dimension.x; i++) {
    //     for (int j = 0; j < dimension.y; j++) {
    //     }
    // }
}*/

void MatchLogic::get_dtos(std::vector<PlayerDTO>& dtos,
                          std::vector<DynamicObjDTO>& objects, std::vector<SoundEventType>& sounds) {
    for (Player &player: players) {

        PlayerDTO dto;

        player.get_data(dto.id, dto.pos.x, dto.pos.y, dto.weapon, dto.helmet, dto.chest_armor,
                        dto.move_action, dto.doing_action, dto.is_alive, dto.aiming_up, dto.hp, dto.munition);
        player.get_sounds(sounds);
        dtos.push_back(dto);
    }

    for (Box& box: boxes){
        if (box.is_spawned()){
            DynamicObjDTO dto = {0, 0, TypeDynamicObject::BOX};
            Tuple position = box.get_spawn_point();
            dto.pos.x = position.x;
            dto.pos.y = position.y;
            objects.push_back(dto);
        }
    }

    for (SpawnPlace &spawn_place: spawn_places) {
        if (spawn_place.is_spawned()){
            DynamicObjDTO dto = {0, 0, TypeDynamicObject::NONE};
            spawn_place.get_data(dto.pos.x, dto.pos.y, dto.type);
            objects.push_back(dto);
        }
    }

    for (DroppedItem &dropped_item: dropped_items) {
        if (dropped_item.is_alive()){
            DynamicObjDTO dto = {0, 0, TypeDynamicObject::NONE};
            dropped_item.get_data(dto.pos.x, dto.pos.y, dto.type);
            objects.push_back(dto);
        }
    }

    for (Bullet bullet: bullets) {
        DynamicObjDTO dto = {0, 0, TypeDynamicObject::PROJECTILE};
        bullet.get_map_info(dto.pos.x, dto.pos.y, dto.type);
        objects.push_back(dto);
    }

    for (const auto& throwable : throwables) {
        DynamicObjDTO dto = {0, 0, TypeDynamicObject::PROJECTILE};
        throwable->get_map_info(dto.pos.x, dto.pos.y, dto.type);
        objects.push_back(dto);
    }
    
    /* // Las bananas estan como throwables!
    for (MapPoint &banana: bananas) {
        DynamicObjDTO dto = {banana.x, banana.y, TypeDynamicObject::THROWN_BANANA};
        objects.push_back(dto);
    }
    
    */

}

void MatchLogic::execute_move_command(int action_type, int index) {
    auto search = command_map.find(action_type);

    if (search == command_map.end()) {
        std::cerr << "No se reconocio la accion " << action_type<< std::endl;
        return;
    }
    search->second(index);
}

void MatchLogic::add_boxes(const std::vector<struct MapPoint>& boxes){
    int id_box = 0;
    for (const struct MapPoint& box: boxes) {
        this->boxes.push_back(Box(id_box, configs.box_health, box.x, box.y));
        //std::cout << "-->ADDED BOX id: "<< id_box<<std::endl;
        id_box++;
    }
}

void MatchLogic::add_items(const std::vector<struct MapPoint>& items){
    int id =0;
    for (const struct MapPoint& item: items) {
        this->spawn_places.push_back(SpawnPlace(item.x, item.y, 16, 16, configs.item_spawn_time, configs.fps, id));
        spawn_places.back().spawn_item(configs.base_munition);
        id++;
    }
}

void MatchLogic::add_blocks(const std::vector<struct MapPoint>& blocks){

    // MULTIPLICA POR EL SIZE!
    for (const struct MapPoint& block: blocks) {
        this->blocks.push_back(MapPoint(16*block.x, 16*block.y));
    }
}

void MatchLogic::add_spawn_points(const std::vector<struct MapPoint>& spawn_points){
    std::cout << "spawn points: " << spawn_points.size() << std::endl;

    for (const struct MapPoint& spawn_point: spawn_points) {
        this->spawn_points.push_back(MapPoint(spawn_point.x, spawn_point.y));

    }
}

void MatchLogic::add_item_spawns(const std::vector<struct MapPoint>& items_spawns){
    int id = 0;
    for (const struct MapPoint& spawn: items_spawns) {
        this->spawn_places.push_back(SpawnPlace(spawn.x * 16, spawn.y *16, 16, 5, configs.item_spawn_time, configs.fps, id));
        spawn_places.back().spawn_item(configs.base_munition);
        id ++;
    }
}

void MatchLogic::add_bullet(Bullet bullet){
    this->bullets.push_back(bullet);
}

void MatchLogic::damage_player(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.take_damage(configs.base_dmg);
            return;
        }
    }
}



void MatchLogic::damage_box(int id,std::vector<GameEvent>& events) {
    for (auto it = boxes.begin(); it!=boxes.end();) {
        if (it->same_id(id)) {
            //std::cout << "----BOX TOOK DMG\n";
            it->take_damage();
            if (it->destroyed()){
                //std::cout << "-----DESTROYED BOX\n";

                Tuple position = it->get_spawn_point();


                // Si es bomba SERIA EXPLOSION ! o asi
                auto weapon(it->get_item(configs.base_munition));
                
                if(weapon == nullptr){
                    events.emplace_back(position.x, position.y, BOX_DESTROYED);
                    events.emplace_back(position.x, position.y, BOMB_EXPLOSION);
                    
                    
                    // Mas que radious square radious!
                    std::vector<Collision> dmg_players;
                    
                    int x_init = position.x-configs.explosion_radius;
                    int y_init = position.y-configs.explosion_radius;
                    
                    
                    colition_map.filter_collisions_area_all(CollisionTypeMap::PLAYER, x_init,y_init
    , 2*configs.explosion_radius, 2*configs.explosion_radius, dmg_players);
                    
                    for(Collision& hitted_player: dmg_players){
                         std::cout << "---> BOMB HITTED PLAYER " << hitted_player.id << std::endl;
                         damage_player(hitted_player.id);
                    }
                    
                    it = boxes.erase(it);
                    return;
                }

                events.emplace_back(position.x, position.y, BOX_DESTROYED);
                dropped_items.push_back(DroppedItem(std::move(weapon), position.x, position.y, 16, 16));
                it = boxes.erase(it);
                return;
            }
            return;
        }
        it ++;
    }
    std::cout << "NOT FOUND BOX FOR TAKE DMG!!" << id<< "\n";

}

void MatchLogic::update_bullets(std::vector<GameEvent>& events){
    for (auto bullet = bullets.begin(); bullet!=bullets.end();) {
        bool impacted = false;
        Collision collision(0, CollisionTypeMap::NONE);
        bullet->get_data(impacted, collision.type, collision.id);
        if (impacted) {
            if (collision.type == CollisionTypeMap::PLAYER) {
                this->damage_player(collision.id);
            }
            if (collision.type == CollisionTypeMap::BOX) {
                this->damage_box(collision.id,events);


            }
            //std::cout << "ERASING BULLET !!\n";
            bullet = bullets.erase(bullet);
        } else {
            bullet->move(colition_map);
            ++bullet;
        }
    }
}


bool MatchLogic::player_slip(int id, int x_item){
    for (Player& player: players) {
        if (player.same_id(id)) {
                        
            std::cout << "FOUND PLAYER WHO TOUCHED BANANA AT x:"<< x_item<<" \n";
            player.slip_impulse(x_item);
            return true;
        }
    }
    return false;
}

void MatchLogic::update_grenades(std::vector<GameEvent>& events){
    for (auto it = throwables.begin(); it!=throwables.end();) {
    
        ThrowableAction action;
        if((*it)->get_action(colition_map, action)){
            std::cout << "ACTION FOR THROWABLE?! " << (int)action << std::endl;
            
            if(action == ERASE_SELF){
               it = throwables.erase(it);
               continue;  
            }
            
            int id = (*it)->activate(bullets, events);
            
            if(action == ThrowableAction::SLIP_PLAYER){
                int x;
                int y;
                (*it)->get_pos(x,y);
                if(player_slip(id, x)){
                    it = throwables.erase(it);
                    continue;
                }
                it ++;
                continue;
            }
            
            it = throwables.erase(it);
            continue;
        }
        it ++;
    }
}



void MatchLogic::update_dropped_items(){
    for (auto it = dropped_items.begin(); it!=dropped_items.end();) {
        if (!it->is_alive()){
            std::cout << "ERASING ITEM !!\n";
            it = dropped_items.erase(it);
        } else {
            it ++;
        }
    }
}

void MatchLogic::clear_players(){
    players.clear();
}

void MatchLogic::update_spawn_places(){
    for (SpawnPlace &spawn: this->spawn_places) {
        spawn.spawn_item(configs.base_munition);
    }
}

void MatchLogic::update_spawn_points(){
    for (SpawnPlace &spawn: this->spawn_places) {
        spawn.pass_time(configs.base_munition);
    }
}

void MatchLogic::clear_objects(){
    //spawn_points.clear();
    boxes.clear();
    //bananas.clear();
    //spawn_places.clear();
    dropped_items.clear();
    throwables.clear();
    bullets.clear();
}

void MatchLogic::resize_map(const int width, const int height){
    colition_map.setSize(16*width, 16*height);
}

void MatchLogic::reset_map(){

    spawn_places.clear();
    spawn_points.clear();
    dropped_items.clear();
    boxes.clear();
    blocks.clear();
    bullets.clear();
    //bananas.clear();
    throwables.clear();
    colition_map.clear_map();
}

void MatchLogic::player_cheat_1() {
    for (Player& player: players) {
        player.cheat_weapon(configs.base_munition);
    }
}

void MatchLogic::player_cheat_2() {
    for (Player& player: players) {
        player.cheat_ammo();
    }
}

void MatchLogic::player_cheat_3() {
    for (Player& player: players) {
        player.cheat_armor();
    }
}

MatchLogic::~MatchLogic() {}
