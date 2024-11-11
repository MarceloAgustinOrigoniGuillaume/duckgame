#include "texture_container.h"

TextureContainer::TextureContainer(SDL2pp::Renderer& renderer) {
    textures.emplace(TextureType::YELLOW_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/yellow_duck.png"));
    textures.emplace(TextureType::GREY_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/grey_duck.png"));
    textures.emplace(TextureType::ORANGE_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/orange_duck.png"));
    textures.emplace(TextureType::WHITE_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/white_duck.png"));
    textures.emplace(TextureType::BACKGROUND,
                     SDL2pp::Texture(renderer, DATA_PATH "/backgrounds/forestNight.png"));
    textures.emplace(TextureType::TREE,
                     SDL2pp::Texture(renderer, DATA_PATH "/notexture.png"));
    textures.emplace(TextureType::BOX,
                     SDL2pp::Texture(renderer, DATA_PATH "/boxes/itemBox1.png"));

    loadMapTextures(renderer, DATA_PATH);
}

TextureType TextureContainer::indexToTextureType(int index) const {
    switch (index) {
        case 1:
            return TextureType::YELLOW_DUCK;
        case 2:
            return TextureType::GREY_DUCK;
        case 3:
            return TextureType::ORANGE_DUCK;
        case 4:
            return TextureType::WHITE_DUCK;
        case 5:
            return TextureType::BACKGROUND;
        case 6:
            return TextureType::TREE;
        case 7:
            return TextureType::BOX;
        default:
            throw std::out_of_range("Invalid texture index");
    }
}

SDL2pp::Texture& TextureContainer::getTexture(int index) {
    TextureType type = indexToTextureType(index);
    return textures.at(type);
}

SDL2pp::Texture& TextureContainer::getTexture(TextureType type) { return textures.at(type); }

SDL2pp::Texture& TextureContainer::getMapTexture(std::string source) {
    try {
        return mapTextures.at(DATA_PATH + source);
    } catch (const std::out_of_range& e) {
        for (const auto& pair : mapTextures) {
            std::cout << "Clave: " << pair.first << std::endl;
        }
        std::cout << "Error NO SE ENCONTRO: " << DATA_PATH + source << std::endl;
        throw e;
    }
}

TextureContainer::~TextureContainer() = default;





void TextureContainer::loadMapTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    loadBackgroundTextures(renderer, root);
    loadBlockTextures(renderer, root);
    loadSpawnPlayerTextures(renderer, root);
    loadSpawnWeaponTextures(renderer, root);
    loadBoxTextures(renderer, root);
    loadDecorationTextures(renderer, root);
}

void TextureContainer::loadBackgroundTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    loadTextures(renderer, root, "/backgrounds");
}

void TextureContainer::loadBlockTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    loadTextures(renderer, root, "/blocks");
}

void TextureContainer::loadSpawnPlayerTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    loadTextures(renderer, root, "/spawns/weapons");
}

void TextureContainer::loadSpawnWeaponTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    loadTextures(renderer, root, "/spawns/players");
}

void TextureContainer::loadBoxTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    loadTextures(renderer, root, "/boxes");
}

void TextureContainer::loadDecorationTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    loadTextures(renderer, root, "/decorations");
}

void TextureContainer::loadTextures(SDL2pp::Renderer& renderer, const std::string& root, const std::string& path) {
    QString fullPath = QString::fromStdString(root + path);
    QDir directory(fullPath);

    QStringList filters;
    filters << "*.png";
    directory.setNameFilters(filters);

    QFileInfoList fileList = directory.entryInfoList(QDir::Files);

    for (const QFileInfo& fileInfo : fileList) {
        std::string filePath = fileInfo.filePath().toStdString();
        mapTextures.emplace(filePath, SDL2pp::Texture(renderer, filePath));
    }
}
