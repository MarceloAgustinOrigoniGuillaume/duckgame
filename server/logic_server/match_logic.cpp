#include "match_logic.h"

#include <iostream>


MatchLogic::MatchLogic(): colition_map(700, 500) {
    this->command_map[PlayerActionType::NONE] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };
    this->command_map[PlayerActionType::MOVE_LEFT] = [this](int index) {
        this->add_player_speed(index, -10, 0);
    };
    this->command_map[PlayerActionType::MOVE_LEFT_END] = [this](int index) {
        this->still_player(index);
    };

    this->command_map[PlayerActionType::MOVE_RIGHT] = [this](int index) {
        this->add_player_speed(index, 10, 0);
    };
    this->command_map[PlayerActionType::MOVE_RIGHT_END] = [this](int index) {
        this->still_player(index);
    };

    this->command_map[PlayerActionType::JUMP] = [this](int index) {
        this->add_player_speed(index, 0, 50);
    };

    this->command_map[PlayerActionType::STAY_DOWN] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };
    this->command_map[PlayerActionType::STAY_DOWN_START] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };
    this->command_map[PlayerActionType::STAY_DOWN_END] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };

    this->command_map[PlayerActionType::FLAPPING_END] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };

    this->command_map[PlayerActionType::AIM_UP_START] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };
    this->command_map[PlayerActionType::AIM_UP_END] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };
    this->command_map[PlayerActionType::SHOOT] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };




    // this->command_map[3] = [this](int index) { this->add_player_speed(index, 0, 0); };

}

void MatchLogic::add_player(int id) {
    players.push_back(Player(id, 10 + id * 50, 50));
    colition_map.add_collision(players.back().get_map_position(), players.back().get_dimension());
}

void MatchLogic::add_player_speed(int id, int speed_x, int speed_y) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.add_speed(speed_x, speed_y);
            return;
        }
    }
}

void MatchLogic::still_player(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.still();
            return;
        }
    }
}

void MatchLogic::update_players() {
    for (Player& player: players) {
        player.update(colition_map);
    }
}

void MatchLogic::update_colition_map() {
    colition_map.clear_objects();
    for (Player& player: players) {
        colition_map.add_collision(player.get_map_position(), player.get_dimension());
    }
    for (Box& box: boxes) {
        if (box.is_spawned()){
            colition_map.add_collision(box.get_spawn_point(), box.get_dimension());
        }
    }
}

/*void MatchLogic::add_colition(PhysicalObject &object) {

    //colition_map.add_colition(object);

    //colition_map.add_temp_collision(position.x + dimension.x, position.y + dimension.y);

    // for (int i = 0; i < dimension.x; i++) {
    //     for (int j = 0; j < dimension.y; j++) {
    //     }
    // }
}*/

void MatchLogic::get_dtos(std::vector<PlayerDTO>& dtos, std::vector<DynamicObjDTO>& objects) {
    for (Player player: players) {

        PlayerDTO dto = {0, false, 0, 0, TypeWeapon::NONE, false, false, TypeMoveAction::NONE};
        player.get_data(dto.id, dto.pos.x, dto.pos.y, dto.weapon, dto.helmet, dto.chest_armor,
                        dto.move_action);

        dtos.push_back(dto);
    }

    for (Box box: boxes){
        DynamicObjDTO dto = {0, 0, TypeDynamicObject::BOX};
        Tuple position = box.get_spawn_point();
        dto.pos.x = position.x;
        dto.pos.y = position.y;
        objects.push_back(dto);
    }

}

void MatchLogic::execute_move_command(int action_type, int index) {
    this->command_map[action_type](index);
}

void MatchLogic::add_boxes(const std::vector<struct MapPoint>& boxes){
    for (const struct MapPoint& box: boxes) {
        this->boxes.push_back(Box(box.x, box.y));
    }
}

MatchLogic::~MatchLogic() {}
