
#include "./match_state.h"

#include <iostream>
#include <utility>
MatchState::MatchState(): running(false), match_logic(), acciones(match_logic) {}

void MatchState::pushAction(const PlayerActionDTO& action) { acciones.push_command(action); }

void MatchState::loop(PlayerContainer& observer) {
    std::vector<unsigned int> ids = observer.getPlayers();
    for (auto id = ids.begin(); id != ids.end();) {
        match_logic.add_player(*id);
        std::cout << "New player added with id: " << *id << std::endl;
        ++id;
    }
    running = true;
    while (running) {
        this->receive_commands();
        // this->execute_commands();
        // this->send_results();
        MatchDto dto = MatchDto(INICIADA, 1);

        // AGREGA JUGADORES!!
        match_logic.get_dtos(dto.players);

        observer.updateState(dto);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void MatchState::receive_commands() {
    ActionCommand command({PlayerActionType::NONE, 0, 0}, &this->match_logic);
    if (acciones.pop_command(command)) {
        command.execute();
    }
}

void MatchState::execute_commands() {
    for (auto command: commands) {
        command.execute();
    }
    commands.clear();
}

void MatchState::stop() { running = false; }

void MatchState::send_results() {}

MatchState::~MatchState() {}
