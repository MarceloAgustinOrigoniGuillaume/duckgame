
#ifndef GRENADE_H
#define GRENADE_H

#include <vector>
#include "server/logic/physical/physical_grenade.h"
#include "common/dtosobject.h"
#include "bullet.h"
#include "server/logic/physical/match_map.h"
#include "server/logic/physical/tuple.h"
#include "throwable.h"

class Grenade : public Throwable{

    private:
        int detonation_time;
        int shoot_time;

    public:
        Grenade(int init_coord_x, int init_coord_y, int id_player, int shoot_time);
        void shoot_right() override;
        void shoot_left() override;
        void shoot_up() override;
        bool exploded(std::vector<Bullet> &bullets, std::vector<MapPoint> &other_objects) override;

};



#endif //GRENADE_H
