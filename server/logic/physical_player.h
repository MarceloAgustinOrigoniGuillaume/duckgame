
#ifndef PHYSICAL_PLAYER_H
#define PHYSICAL_PLAYER_H


#include "physical_object.h"
#include <vector>
#include "common/dtosplayer.h"
#include "match_map.h"
#include "tuple.h"
#include "shooting_direction.h"
#include "collision.h"
#include "type_collision.h"
#include "server/core/configuration.h"

class MatchMap;

enum PlayerMovingDir {
    NOT_SETTED = -3,
    NO_MOVE = 0,
    MOVING_LEFT = -1,
    MOVING_RIGHT = 1,
};

struct Impulse{
    int left_over_vel;
    int acc;
    int steps;
    Impulse(int left_over_vel, int acc, int dur):left_over_vel(left_over_vel),acc(acc),steps(dur) {}
};

class PhysicalPlayer: public PhysicalObject {

    private:
        static constexpr int PLAYER_WIDTH = 10;
        static constexpr int PLAYER_HEIGHT = 22;
        static constexpr int FLAP_ATTEMPS = 10;

        Tuple initial_position;
        const Configuration& configs;
        int flap_attemps;
        int steps_deaccelerate;
        PlayerMovingDir moving_dir;
        
        bool on_air;
        bool out_of_map;
        bool hold_flap;
        bool stopped_x;
        
        std::vector<struct Impulse> impulses;

    public:
        PhysicalPlayer(int init_coord_x, int init_coord_y, const Configuration& _configs);
        
        bool isOnAir() const;
        void react_to_sides_collision(Collision collision) override;
        void react_to_down_collision(Collision collision) override;
        void react_to_up_collision(Collision collision) override;
        void react_to_out_of_map() override;
        bool is_out_of_map();
        void stay_down_start();
        void stay_down_end();
        
        bool jump_start();
        bool try_flap_start();
        
        void jump_end();
        void update_action(TypeMoveAction& move_action);
        
        
        void add_impulse_x(int vel_max, int durations);

        void check_moving_dir(const MatchMap& colition_map);
        
        void undo_moving(PlayerMovingDir mov_dir);        
        void change_moving(PlayerMovingDir new_dir);

        void stop_moving_x();

};

#endif  // PHYSICAL_PLAYER_H
