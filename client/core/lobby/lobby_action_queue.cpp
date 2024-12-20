#include "./lobby_action_queue.h"

static const char * RANDOM_MAP = "random map";


LobbyActionQueue::LobbyActionQueue() {}

void LobbyActionQueue::close() { actions.close(); }

void LobbyActionQueue::doaction(const lobby_action& action) { actions.push(action); }


lobby_action LobbyActionQueue::popaction() { return actions.pop(); }


const char * LobbyActionQueue::randomMapLabel() const{
     return RANDOM_MAP;
}

const std::string& LobbyActionQueue::getMapName() const { return mapname; }

void LobbyActionQueue::notifyStart(const std::string& map) {
    mapname = map;
    lobby_action action(PLAYER_READY, 0);
    actions.push(action);
}
