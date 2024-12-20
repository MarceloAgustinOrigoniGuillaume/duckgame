

#ifndef PHYSICAL_BULLET_H
#define PHYSICAL_BULLET_H

#include "server/logic/physical/physical_object.h"
#include "common/dtosobject.h"
#include "server/logic/physical/collision.h"
#include "type_collision.h"

class PhysicalBullet: public PhysicalObject{

    private:

        bool impacted;
        Collision impacted_collision;

        bool impacted_up_or_down;
        bool impacted_sides;

        //este atributo no deberia ser parte del cuerpo fisico, pero
        //lo pongo aca de forma provisoria
        //TypeDynamicObject type;

    public:
        //PhysicalBullet(int init_coord_x, int init_coord_y, TypeDynamicObject type);
        PhysicalBullet(int init_coord_x, int init_coord_y);

        void react_to_sides_collision(Collision collision) override;
        void react_to_down_collision(Collision collision) override;
        void react_to_up_collision(Collision collision) override;
        void react_to_out_of_map() override;

        void shoot_right();
        void shoot_left();
        void shoot_up();

        void get_data(bool &impacted, CollisionTypeMap &type, int &id);
        void get_map_info(int &pos_x, int &pos_y);
        void reset_data();

        void bounce();

};



#endif //PHYSICAL_BULLET_H
