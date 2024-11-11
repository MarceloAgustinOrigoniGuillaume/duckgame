#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Drawer;

enum MapObjectType {
    Background,
    Block,
    SpawnPlayer,
    SpawnWeapon,
    Box,
    Decoration,
    Empty
};

struct MapObjectData {
    int row;
    int column;
    MapObjectType mapObjectType;
    std::string texture;
};

class Map {
private:
    const int width = 20;
    const int height = 10;
    const int textureSize = 16;

    MapObjectData background;
    std::vector<MapObjectData> decorations;
    std::vector<MapObjectData> blocks;
    std::vector<MapObjectData> spawnPlayers;
    std::vector<MapObjectData> spawnWeapons;

public:
    explicit Map();

    void drawBackground(Drawer& drawer);

    void drawBlocks(Drawer& drawer);

    void drawDecorations(Drawer& drawer);

    void drawSpawnPlayers(Drawer& drawer);

    void drawSpawnWeapons(Drawer& drawer);

    void drawMapObjects(Drawer& drawer, std::vector<MapObjectData> mapObjects);

    ~Map();
};

#endif
