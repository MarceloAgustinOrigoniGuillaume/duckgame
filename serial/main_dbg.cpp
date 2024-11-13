#include <iostream>
#include <string>

#include "./map_deserializer.h"
#include "./map_loader.h"
#include "./map_serializer.h"
#include "common/clock.h"

static void deserial(const std::string& file) {
    MapDeserializer serial(file);
    serial.dosome();
}
static void create(const std::string& file) {

    MapSerializer serial(100, 550);
    std::string name("NAME");
    std::string name1("OT");
    std::string name2("LAS");

    for (int i = 0; i < 50; i += 3) {
        serial.addBlock(2, 3 + i, name);
    }
    for (int i = 0; i < 25; i += 3) {
        serial.addBlock(5 + i, 3 + i, name1);
    }
    for (int i = 50; i < 100; i += 3) {
        serial.addDecoration(2, 3 + i, 2, name2);
    }

    serial.addBox(4, 3);
    serial.addBox(6, 3);
    serial.addBox(6, 4);
    serial.addBox(7, 3);

    std::string pl = "playswp";

    serial.addItemSpawn(12, 3, pl);
    serial.addItemSpawn(99, 3, pl);

    serial.addPlayerSpawn(14, 3, pl);
    serial.addPlayerSpawn(23, 3, pl);

    serial.save(file);
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No se paso por parametro el archivo target!\n";
        return 1;
    }

    Clock clock(30);
    clock.resetnow();
    std::string file("res/maps/");
    file.append(argv[1]);
    create(file);
    int ms = clock.measure();


    std::cout << "--->TOOK " << ms << "ms?" << std::endl;


    //  deserial(file);

    std::cout << "ACT UPON " << argv[1] << std::endl;

    clock.resetnext();

    MapLoader loader;

    const MapInfo& info = loader.loadMap(argv[1]);
    const MapInfo& info2 = loader.loadMap(argv[1]);

    clock.tick();
    clock.tick();
    clock.tick();
    clock.tick();

    std::cout << "TICK COUNT AFTER IS " << clock.tickcount() << std::endl;

    std::cout << "MAP 1 SIZE IS " << info.size.x << " , " << info.size.y
              << " BACKGROUND: " << (int)(info.bk) << std::endl;
    std::cout << "MAP 2 SIZE IS " << info2.size.x << " , " << info2.size.y
              << " BACKGROUND: " << (int)(info2.bk) << std::endl;

    std::cout << "Map 1 player count " << info.spawns_player.size() << std::endl;

    for (const struct MapPoint& point: info.spawns_player) {
        std::cout << "Player spawn at " << point.x << " , " << point.y << std::endl;
    }

    std::cout << "Map 2 item spawn count " << info2.spawns_items.size() << std::endl;

    for (const struct MapPoint& point: info2.spawns_items) {
        std::cout << "Item spawn at " << point.x << " , " << point.y << std::endl;
    }

    loader.removeMap(info.mapname);
    std::cout << "DELETED MAP 1 " << info.mapname << std::endl;
    loader.removeMap(info2.mapname);


    return 0;
}
