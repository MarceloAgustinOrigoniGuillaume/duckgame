#include "./map_deserializer.h"

#include <fstream>
#include <iostream>

#include "common/core/liberror.h"

MapDeserializer::MapDeserializer(const std::string& src): srcmap(src), reader(srcmap) {
}

// Metodos delegatorios. Capaz no haria falta exponerlos en esta clase.
void MapDeserializer::readSize(struct MapPoint& size) {
     reader.readSize(size);
}

void MapDeserializer::readBackground(std::string& background) {
     reader.readBackground(background);
}

void MapDeserializer::readBlocksZ(uint16_t& z) { 
     reader.readBlocksZ(z);
}

void MapDeserializer::readBoxesZ(uint16_t& z) {
     reader.readBoxesZ(z);
}

void MapDeserializer::readBoxesTexture(std::string& box_tex) {
     reader.readBoxesTexture(box_tex);
}


void MapDeserializer::readTextures(std::vector<std::string>& res) {
     reader.readTextures(res);
}




// Metodos especificos para el cargado para el server.
const std::string& MapDeserializer::getMapName() const { return srcmap; }

void MapDeserializer::readDecorations(std::vector<struct DecorationDTO>& res) {
    read_seq_t decorations = reader.getDecorations();
    read_seq_t spawns_items = reader.getItemSpawns();
    read_seq_t spawns_players = reader.getPlayerSpawns();
    uint16_t z_spawns;
    
    readBlocksZ(z_spawns);
    
    int size = decorations.num_children();
    int size_itms = spawns_items.num_children();
    int size_players = spawns_players.num_children();
    res.reserve(size+size_itms+size_players);

    for (int i = 0; i < size; i++) {
        read_item_t item = decorations[i];
        reader.assertIsMap(item);        
        
        DecorationDTO& decoration = res.emplace_back();
        
        reader.readItemPosition(item, decoration.pos);
        reader.readItemTexture(item, decoration.texture_id);
        reader.readItemZInd(item, decoration.z_ind);
    }
    
  
    // Ahora los spawns...
    for (int i = 0; i < size_itms; i++) {
        read_item_t item = spawns_items[i];
        reader.assertIsMap(item);        
        DecorationDTO& decoration = res.emplace_back();
        
        reader.readItemPosition(item, decoration.pos);
        reader.readItemTexture(item, decoration.texture_id);
        decoration.z_ind = z_spawns;
    }

    for (int i = 0; i < size_players; i++) {
        read_item_t item = spawns_players[i];
        reader.assertIsMap(item);
        
        DecorationDTO& decoration = res.emplace_back();
        
        reader.readItemPosition(item, decoration.pos);
        reader.readItemTexture(item, decoration.texture_id);
        decoration.z_ind = z_spawns;
    }        
}


void MapDeserializer::readBlocks(std::vector<struct BlockDTO>& res) {
    read_seq_t blocks = reader.getBlocks();

    int size_blocks = blocks.num_children();

    res.reserve(size_blocks);
    
    for (int i = 0; i < size_blocks; i++) {
        read_item_t item = blocks[i];
        reader.assertIsMap(item);        

        BlockDTO& block = res.emplace_back();
        reader.readItemPosition(item, block.pos);
        reader.readItemTexture(item, block.texture_id);
    }
  
}

void MapDeserializer::readPlayerSpawns(std::vector<struct MapPoint>& res) {
    reader.readPoints(reader.getPlayerSpawns(), res);
}
void MapDeserializer::readItemSpawns(std::vector<struct MapPoint>& res) {
    reader.readPoints(reader.getItemSpawns(), res);
}

void MapDeserializer::readBoxes(std::vector<struct MapPoint>& res) {
    reader.readPoints(reader.getBoxes(), res);
}


void MapDeserializer::loadMapInfo(struct MapInfo& info) {
    reader.readSize(info.size);

    reader.readBlocksZ(info.blocks_z);
    reader.readBoxesZ(info.boxes_z);

    reader.readBackground(info.background);
    reader.readBoxesTexture(info.boxes_tex);

    reader.readTextures(info.textures);
    readBlocks(info.blocks);
    readDecorations(info.decorations);

    info.map_id = srcmap;
}


void MapDeserializer::loadObjectsInfo(struct ObjectsInfo& info) {
    readPlayerSpawns(info.player_spawns);
    readItemSpawns(info.item_spawns);
    readBoxes(info.boxes);

    // Read blocks .. again? NAA
}
