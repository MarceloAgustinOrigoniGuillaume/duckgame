#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <memory>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include <QDir>
#include <QFileInfoList>

enum class TextureType {
    YELLOW_DUCK = 1,
    GREY_DUCK,
    ORANGE_DUCK,
    WHITE_DUCK,

    BACKGROUND,
    TREE,
    BOX,
    COWBOY_GUN
};

class TextureContainer {
private:
    std::unordered_map<TextureType, SDL2pp::Texture>
            textures;  // cppcheck-suppress unusedStructMember

    std::unordered_map<std::string, SDL2pp::Texture>
            mapTextures;  // cppcheck-suppress unusedStructMember

    // No va a hacer falta cuando se setee previamente el tipo de textura
    TextureType indexToTextureType(int index) const;

public:
    explicit TextureContainer(SDL2pp::Renderer& renderer);

    SDL2pp::Texture& getTexture(int index);

    SDL2pp::Texture& getTexture(TextureType type);

    SDL2pp::Texture& getMapTexture(std::string source);

    ~TextureContainer();

private:
    void loadMapTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void loadBackgroundTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void loadBlockTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void loadSpawnPlayerTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void loadSpawnWeaponTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void loadBoxTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void loadDecorationTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void loadTextures(SDL2pp::Renderer& renderer, const std::string& root, const std::string& path);
};

#endif
