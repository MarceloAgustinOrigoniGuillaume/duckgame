
#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "match_map.h"
#include "tuple.h"

class MatchMap;

class PhysicalObject {

protected:
    Tuple position;
    Tuple dimension;
    Tuple speed;
    Tuple acceleration;
    float time_step;

public:
    PhysicalObject(int position_x, int position_y, int dimension_x, int dimension_y);

    void add_speed(int speed_x, int speed_y);
    void add_acceleration(int acceleration_x, int acceleration_y);

    void move(const MatchMap& colition_map);
    bool detect_x_collision(const MatchMap& colition_map, const int diff, bool &is_player, int &id_player);
    bool detect_y_collision(const MatchMap& colition_map, const int diff, bool &is_player, int &id_player);

    virtual void react_to_sides_collision(bool is_player, int id_player) = 0;
    virtual void react_to_down_collision(bool is_player, int id_player) = 0;
    virtual void react_to_up_collision(bool is_player, int id_player) = 0;

    Tuple get_position();
    Tuple get_dimension();
    void get_real_position(int& x, int& y);

    virtual ~PhysicalObject() = default;
};


#endif  // PHYSICAL_OBJECT_H
