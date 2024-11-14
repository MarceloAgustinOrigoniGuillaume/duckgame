#include "./simpleeventlistener.h"

#include <iostream>

SimpleEventListener::SimpleEventListener() {}

void SimpleEventListener::matchUpdated(const MatchDto& state) {
    updates.push(state);
    /*
    for (const PlayerDTO& player: state.players) {
        std::cerr << "-->ply " << (int)player.id << " at " << player.pos.x << "," << player.pos.y
                  << std::endl;
    }
    */
    int count = 0;
    for (const DynamicObjDTO& obj: state.objects) {
        if(obj.type != TypeDynamicObject::PROJECTILE){
            continue;
        }
        
        std::cerr << "-->obj "<< count <<" " << (int)obj.type << " at " << obj.pos.x << "," << obj.pos.y
                  << std::endl;
        count++;
    }
}
void SimpleEventListener::matchFinished(const MatchDto& final_info) {
    updates.push(final_info);
    updates.close();
    std::cout << "MATCH FINISHED " << std::endl;
}

bool SimpleEventListener::try_update(MatchDto& last_update) { return updates.try_pop(last_update); }
bool SimpleEventListener::isclosed() { return updates.isclosed(); }
void SimpleEventListener::disconnect() { updates.close(); }


SimpleEventListener::~SimpleEventListener() {
    // updates.close();
}
