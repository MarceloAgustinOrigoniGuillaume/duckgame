#include "./configuration.h"

#include "serial/config_reader.h"
#include "common/serialerror.h"
#include <iostream>

#define FPS 30
#define MS_FPS 1000 / FPS

// Defaults vls
Configuration::Configuration(): 
    base_dmg(1),
    base_munition(1),
    gravity(10),
    explosion_radius(1),
    player_speed(1),
    player_health(3),
    player_jmp_force(40),
    player_flap_force(10),
    player_flaps(9),
    flap_grav(3),
    fps(FPS),
    frame_delay(MS_FPS),
    rounds_per_set(5),
    wins_needed(10),
    armor_health(1),
    box_health(1),
    item_spawn_time(1)
    {}


Configuration::Configuration(const char* config): Configuration() {
        std::cout << "Loading configs from " << config<<std::endl;
        try{    
            ConfigReader reader(config);
            
            reader.readBaseDmgMunition(base_dmg, base_munition);
            // Dejenme usar printf!!!!
            printf("Base dmg: %u base munition: %u\n",base_dmg, base_munition);
            
            //reader.readMagnumInfo(magnum_dmg, magnum_munition);
            //printf("magnum dmg: %u magnum munition: %u\n",magnum_dmg, magnum_munition);

            reader.readPlayerInfo(player_health, player_speed,player_jmp_force,
                                  player_flap_force,player_flaps,flap_grav);
            printf("player hp: %u speed: %u jmp force: %d\n",player_health, player_speed,player_jmp_force);
            printf("player flap_force: %d flap_count: %u flap grav: %d\n",player_flap_force,player_flaps,flap_grav);
            
            
            
            reader.readDefenseInfo(armor_health, helmet_health);
            printf("armor hp: %u helmet_hp: %u\n",armor_health, helmet_health);
            
            reader.readExpRadius(explosion_radius);
            printf("exp radius: %u\n",explosion_radius);
            
            reader.readBoxHealth(box_health);
            printf("box health: %u\n",box_health);

            reader.readItemSpawnTime(item_spawn_time);
            printf("item spawn time: %u\n",item_spawn_time);

            reader.readMSDelay(fps, frame_delay);
            printf("fps: %d delay frame: %ums\n",fps,frame_delay);
            reader.readGravity(gravity);
            printf("gravity : %d\n",gravity);

            reader.readWinsNeeded(wins_needed);
            printf("wins needed : %u\n",wins_needed);
            if(wins_needed> 255){
                wins_needed  = 255;
            }

            reader.readRoundsPerSet(rounds_per_set);
            
            if(rounds_per_set > wins_needed){
                rounds_per_set  = wins_needed;
            }
            printf("rounds per set : %u\n",rounds_per_set);
            
            
        } catch(const SerialError& error){
            std::cerr << "Failed read of configurations! " << error.what() << std::endl;
        }        
    }

