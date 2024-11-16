
#include "./match_state.h"

#include <iostream>
#include <utility>

#include "common/clock.h"

#define FPS 30
#define MS_FPS 1000 / FPS

MatchState::MatchState(): running(false), match_logic(), acciones(match_logic) {}

void MatchState::pushAction(const PlayerActionDTO& action) { acciones.push_command(action); }

void MatchState::playRound(MatchObserver& observer, MatchStatsInfo& stats) {
    stats.state = INICIADA;
    // start_players(observer);
    Clock clock(MS_FPS);  // 16ms sleep == 60 frames por segundo aprox. 30 = 30 fps
    clock.resetnext();

    while ((running && clock.tickcount() < FPS * 20) && id_alive_players.size() > 1) {
        //std::cout << "LOOP COUNT " << clock.tickcount()<< std::endl;
        this->step();
        this->send_results(observer);
        clock.tickNoRest();

    }

    this->calculate_game_results(stats, id_alive_players[0]);

    std::cout << "FINISHED TICK COUNT OF 90!?" << clock.tickcount()<<std::endl;
    /*
    if(stats.numronda >= 5){ // Termino la partida!
        stats.state = TERMINADA;
        stats.champion_player = 1; //buscar ganador
    } else{ // Termino la ronda o asi. Podria seguir internamente. O no.
        stats.state = PAUSADA; // Para probar.
        stats.numronda++;
        //stats.state = ROUND_END;  // Capaz a futuro para mandar las stats del round.
    }*/
}

void MatchState::calculate_game_results(MatchStatsInfo& stats, int actual_winner){

    for (PlayerStatDto player : stats.stats ) {
        if (player.id == actual_winner){
            player.wins ++;
        }
    }
    if (stats.numronda >= 5){
        int id_champion = 0;
        if (only_one_winner(stats, id_champion)){
            stats.state = TERMINADA;
            stats.champion_player = id_champion;
        } else {
            stats.state = PAUSADA;
        }
    } else {
        stats.state = ROUND_END;
        stats.numronda++;
    }
}

bool MatchState::only_one_winner(MatchStatsInfo& stats, int &id_champion){

    bool only_one_winner = false;
        int maximum_number_of_wins = 0;
        int id_champion_player = 0;
        for (PlayerStatDto player : stats.stats ) {
            if (player.wins > maximum_number_of_wins){
                only_one_winner = true;
                maximum_number_of_wins = player.wins;
                id_champion_player = player.id;
            } else if (player.wins == maximum_number_of_wins){
                only_one_winner = false;
                id_champion_player = 0;
            }
        }
    id_champion = id_champion_player;
    return only_one_winner;
}

void MatchState::start_players(MatchObserver& observer, MatchStatsInfo& stats) {

    stats.stats.clear();
    id_alive_players.clear();
    std::vector<unsigned int> ids = observer.getPlayers();
    for (auto id = ids.begin(); id != ids.end();) {
        stats.stats.push_back(PlayerStatDto(*id, 0));
        id_alive_players.push_back(*id);
        match_logic.add_player(*id);
        std::cout << "New player added with id: " << *id << std::endl;
        ++id;
    }

    running = true;
}

void MatchState::step() {
    this->receive_commands();
    this->execute_commands();
    match_logic.update_colition_map();
    match_logic.update_players(this->id_alive_players);
    match_logic.update_bullets();
}


void MatchState::receive_commands() {
    ActionCommand command({PlayerActionType::NONE, 0, 0}, &this->match_logic);
    while (acciones.pop_command(command)) {
        commands.push_back(command);
    }
}

void MatchState::execute_commands() {
    for (auto command: commands) {
        command.execute();
    }
    commands.clear();
}

void MatchState::stop() { running = false; }

void MatchState::send_results(MatchObserver& observer) {
    MatchDto dto;
    match_logic.get_dtos(dto.players, dto.objects);
    observer.updateState(dto);
}

void MatchState::add_objects(const struct ObjectsInfo& objects_info) {
    match_logic.add_boxes(objects_info.boxes);
    match_logic.add_items(objects_info.item_spawns);
}

MatchState::~MatchState() {}
