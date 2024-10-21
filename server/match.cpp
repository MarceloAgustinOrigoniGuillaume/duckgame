#include "./match.h"

#include <iostream>

#include "./gameerror.h"

Match::Match(lobbyID _id, Queue<class ActionCommand> &queue): id(_id), players(), logic(), looper(this->logic),
    actions(queue, logic){}


// Protected// friend accessed methods
void Match::addPlayer(ControlledPlayer* player) { players.add(player); }

void Match::init() {
    if (is_alive()) {
        throw GameError("Tried to start a match already started!!\n");
    }
    start();
}

void Match::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    players.removeAll();
    actions.close();

    join();
}


// General/public methods.

bool Match::operator==(const Match& other) const { return this->id == other.id; }


lobbyID Match::getID() const { return this->id; }

// Metodos delegatorios.
void Match::notifyAction(const PlayerActionDTO&& action) {
    if (_keep_running) {
        actions.push_command(action);
    }
}

void Match::run() {

    looper.loop(/*players, */actions);
    // Checkea si el finish fue natural o forzado.
}

bool Match::isrunning() const { return _is_alive; }

Match::~Match() { finish(); }
