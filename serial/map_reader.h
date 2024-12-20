#ifndef LIB_MapReader_H
#define LIB_MapReader_H

// Tomado de https://github.com/biojppm/rapidyaml/blob/master/samples/quickstart.cpp
#if defined(RYML_SINGLE_HEADER)  // using the single header directly in the executable
#define RYML_SINGLE_HDR_DEFINE_NOW
#include <ryml_all.hpp>
#elif defined(RYML_SINGLE_HEADER_LIB)  // using the single header from a library
#include <ryml_all.hpp>
#else
#include <ryml.hpp>
// <ryml_std.hpp> is needed if interop with std containers is
// desired; ryml itself does not use any STL container.
// For this sample, we will be using std interop, so...
#include <c4/format.hpp>  // needed for the examples below
#include <ryml_std.hpp>   // optional header, provided for std:: interop
#endif

#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "common/dtosobject.h"

//const ryml::ConstNodeRef
typedef ryml::NodeRef read_seq_t;
typedef ryml::NodeRef read_item_t;

class MapReader {
public:
    static const char* SIZE_X;       // cppcheck-suppress unusedStructMember
    static const char* SIZE_Y;       // cppcheck-suppress unusedStructMember
    static const char* BACKGROUND;   // cppcheck-suppress unusedStructMember
    static const char* TEXTURES;     // cppcheck-suppress unusedStructMember
    static const char* BLOCKS;       // cppcheck-suppress unusedStructMember
    static const char* DECORATIONS;  // cppcheck-suppress unusedStructMember
    static const char* BOXES;        // cppcheck-suppress unusedStructMember

    static const char* ITEM_SPAWNS;    // cppcheck-suppress unusedStructMember
    static const char* PLAYER_SPAWNS;  // cppcheck-suppress unusedStructMember


    static const char* POINT_X;  // cppcheck-suppress unusedStructMember
    static const char* POINT_Y;  // cppcheck-suppress unusedStructMember

    static const char* BLOCK_Z;  // cppcheck-suppress unusedStructMember
    static const char* BOX_Z;    // cppcheck-suppress unusedStructMember
    static const char* BOX_TEX;  // cppcheck-suppress unusedStructMember

    static const char* BLOCK_TEX;  // cppcheck-suppress unusedStructMember

    static const char* DECORATION_Z;  // cppcheck-suppress unusedStructMember

protected:
    //size_t root_id;
    ryml::Tree tree;  // cppcheck-suppress unusedStructMember
    
    ryml::NodeRef root;
public:
    explicit MapReader(const std::string& src);
    // Asumamos por ahora que no se quiere permitir copias..
    MapReader(const MapReader&) = delete;
    MapReader& operator=(const MapReader&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapReader(MapReader&&) = delete;
    MapReader& operator=(MapReader&&) = delete;

    void assertIsMap(read_item_t& item);
    bool checkInvalid(read_item_t& item);
    bool checkIsSeq(read_item_t& item);

    // Loadings de datos en si.
    void readBackground(std::string& background);
    void readBlocksZ(uint16_t& blocks_z);
    void readBoxesZ(uint16_t& boxes_z);
    
    void readTextures(std::vector<std::string>& out);
    
    void readSize(struct MapPoint& size);
    
    // No es necesario seguro.?
    void readBoxesTexture(std::string& box_tex);
        
    
    void readItemPosition(read_item_t& item, struct MapPoint& out);
    void readItemZInd(read_item_t& item, uint16_t& out);
    void readItemTexture(read_item_t& item, uint8_t& out);
      
      
    // Uno utilitario en si.
    void readPoints(read_seq_t list, std::vector<struct MapPoint>& out);

    // Accesos a iteradores/secuencias de elementos. Sin pasarlos a vector
    // Para hacerlo mas eficiente.
    // Se podria hacer el agregado a un vector tmbn.
    read_seq_t getBlocks();
    read_seq_t getDecorations();
    read_seq_t getItemSpawns();
    read_seq_t getPlayerSpawns();
    read_seq_t getBoxes();
    
};
#endif
