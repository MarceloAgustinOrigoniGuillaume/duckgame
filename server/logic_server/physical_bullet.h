

#ifndef PHYSICAL_BULLET_H
#define PHYSICAL_BULLET_H

#include "physical_object.h"
#include "common/dtosobject.h"

class PhysicalBullet: public PhysicalObject{

    private:

        bool impacted;
        bool impacted_in_player;
        int id_impacted_player;

        //este atributo no deberia ser parte del cuerpo fisico, pero
        //lo pongo aca de forma provisoria
        TypeDynamicObject type;

    public:
        PhysicalBullet(int init_coord_x, int init_coord_y, TypeDynamicObject type);
        PhysicalBullet(int init_coord_x, int init_coord_y);

        void react_to_sides_collision(bool is_player, int id_player) override;
        void react_to_down_collision(bool is_player, int id_player) override;
        void react_to_up_collision(bool is_player, int id_player) override;

        void shoot_right();
        void shoot_left();
        void shoot_up();

        void get_data(bool &impacted, bool &impacted_in_player, int &id_impacted_player);
        void get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type);

};



#endif //PHYSICAL_BULLET_H
