#ifndef LOADER_H
#define LOADER_H

#include <QDir>
#include <QFileInfoList>
#include <QPixmap>

#include <string>
#include <vector>



class Loader {
private:
    std::vector<Texture> backgrounds;
    std::vector<Texture> blocks;
    std::vector<Texture> boxes;
    std::vector<Texture> spawnPlayers;
    std::vector<Texture> spawnWeapons;
    std::vector<Texture> decorations;

public:
    explicit Loader(const std::string& root);

    std::vector<std::string> backgroundNames();
    std::vector<std::string> blockNames();
    std::vector<std::string> boxesNames();
    std::vector<std::string> spawnPlayersNames();
    std::vector<std::string> spawnWeaponsNames();
    std::vector<std::string> decorationNames();

    Texture backgroundAt(size_t index);
    Texture blockAt(size_t index);
    Texture boxAt(size_t index);
    Texture spawnPlayerAt(size_t index);
    Texture spawnWeaponAt(size_t index);
    Texture decorationAt(size_t index);

    size_t backgroundsSize();
    size_t blocksSize();
    size_t boxesSize();
    size_t spawnPlayersSize();
    size_t spawnWeaponsSize();
    size_t decorationsSize();

    ~Loader();

private:
    void loadBackgrounds(const std::string& root);

    void loadBlocks(const std::string& root);

    void loadBoxes(const std::string& root);

    void loadSpawnPlayers(const std::string& root);

    void loadSpawnWeapons(const std::string& root);

    void loadDecorations(const std::string& root);

    void load(const std::string& root, const std::string& path, MapObjectType mapObjectType, std::vector<Texture>& textures);

    std::vector<std::string> names(const std::vector<Texture>& textures);
};

#endif
