
#ifndef BULLET_H
#define BULLET_H

#include "server/logic/physical/physical_bullet.h"
#include "server/logic/physical/match_map.h"
#include "common/dtosobject.h"
#include "server/logic/physical/tuple.h"

class Bullet {

    private:
        int range;
        int id_player;
        int dmg;
        Tuple speed;
        PhysicalBullet physical_bullet;
        TypeDynamicObject type;
        bool bounce;

    public:
        Bullet(int init_coord_x, int init_coord_y, int range, TypeDynamicObject type, int id_player,int dmg);
        Bullet(int init_coord_x, int init_coord_y, int range, TypeDynamicObject type, int id_player,int dmg, bool bounce);
        void move(const MatchMap& colition_map);
        void get_data(bool &impacted, CollisionTypeMap &type, int &id);
        void get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type);
        void shoot_right();
        void shoot_left();
        void shoot_up();
        void add_speed(int speed_x, int speed_y);
        int get_dmg() const;
};



#endif //BULLET_H
