#include "map.h"
#include "drawer.h"

Map::Map() {
    background = {-1, -1, MapObjectType::Background, "/backgrounds/forest2.png"};

    decorations = {
        {0, 0, MapObjectType::Decoration, "/decorations/notexture.png"},
        {0, 19, MapObjectType::Decoration, "/decorations/notexture.png"},
        {9, 0, MapObjectType::Decoration, "/decorations/notexture.png"},
        {9, 19, MapObjectType::Decoration, "/decorations/notexture.png"}
    };

    blocks = {
        {6, 2, MapObjectType::Block, "/blocks/52.png"},
        {6, 3, MapObjectType::Block, "/blocks/31.png"},
        {6, 4, MapObjectType::Block, "/blocks/32.png"},
        {6, 5, MapObjectType::Block, "/blocks/32.png"},
        {6, 6, MapObjectType::Block, "/blocks/32.png"},
        {6, 7, MapObjectType::Block, "/blocks/32.png"},
        {6, 8, MapObjectType::Block, "/blocks/32.png"},
        {6, 9, MapObjectType::Block, "/blocks/32.png"},
        {6, 10, MapObjectType::Block, "/blocks/32.png"},
        {6, 11, MapObjectType::Block, "/blocks/32.png"},
        {6, 12, MapObjectType::Block, "/blocks/32.png"},
        {6, 13, MapObjectType::Block, "/blocks/32.png"},
        {6, 14, MapObjectType::Block, "/blocks/32.png"},
        {6, 15, MapObjectType::Block, "/blocks/32.png"},
        {6, 16, MapObjectType::Block, "/blocks/36.png"},
        {6, 17, MapObjectType::Block, "/blocks/53.png"}
    };

    spawnPlayers = {
        {5, 9, MapObjectType::SpawnPlayer, "/spawns/players/respawner.png"}
    };

    spawnWeapons = {
        {5, 5, MapObjectType::SpawnWeapon, "/spawns/weapons/gunSpawner1.png"}
    };
/*
    {-1, -1, Background, "/backgrounds/forest2.png"}
    {6, 2, Block, "/blocks/52.png"}
    {6, 3, Block, "/blocks/31.png"}
    {6, 4, Block, "/blocks/32.png"}
    {6, 5, Block, "/blocks/32.png"}
    {6, 6, Block, "/blocks/32.png"}
    {6, 7, Block, "/blocks/32.png"}
    {6, 8, Block, "/blocks/32.png"}
    {6, 9, Block, "/blocks/32.png"}
    {6, 10, Block, "/blocks/32.png"}
    {6, 11, Block, "/blocks/32.png"}
    {6, 12, Block, "/blocks/32.png"}
    {6, 13, Block, "/blocks/32.png"}
    {6, 14, Block, "/blocks/32.png"}
    {6, 15, Block, "/blocks/32.png"}
    {6, 16, Block, "/blocks/36.png"}
    {6, 17, Block, "/blocks/53.png"}
    {5, 9, SpawnPlayer, "/spawns/players/respawner.png"}
    {5, 5, SpawnWeapon, "/spawns/weapons/gunSpawner1.png"}
    {5, 14, Box, "/boxes/itemBox1.png"}
    {0, 0, Decoration, "/decorations/notexture.png"}
    {0, 19, Decoration, "/decorations/notexture.png"}
    {9, 0, Decoration, "/decorations/notexture.png"}
    {9, 19, Decoration, "/decorations/notexture.png"}
*/
}

void Map::drawBackground(Drawer& drawer) {
    drawer.drawBackground(background);
}

void Map::drawBlocks(Drawer& drawer) {
    drawMapObjects(drawer, blocks);
}

void Map::drawDecorations(Drawer& drawer) {
    drawMapObjects(drawer, decorations);
}

void Map::drawSpawnPlayers(Drawer& drawer) {
    drawMapObjects(drawer, spawnPlayers);
}

void Map::drawSpawnWeapons(Drawer& drawer) {
    drawMapObjects(drawer, spawnWeapons);
}

void Map::drawMapObjects(Drawer& drawer, std::vector<MapObjectData> mapObjects) {
    for (const MapObjectData& mapObject : mapObjects) {
        drawer.drawMapObject(mapObject);
    }
}

Map::~Map() {}