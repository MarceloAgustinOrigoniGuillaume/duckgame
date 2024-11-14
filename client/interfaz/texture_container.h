#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

enum class TextureType {
    YELLOW_DUCK = 1,
    GREY_DUCK,
    ORANGE_DUCK,
    WHITE_DUCK,

    BACKGROUND,
    TREE,
    BOX
};

class TextureContainer {
private:
    std::unordered_map<TextureType, SDL2pp::Texture>
            textures;                              // cppcheck-suppress unusedStructMember
    std::vector<SDL2pp::Texture> textures_blocks;  // cppcheck-suppress unusedStructMember

    // No va a hacer falta cuando se setee previamente el tipo de textura
    TextureType indexToTextureType(int index) const;

public:
    explicit TextureContainer(SDL2pp::Renderer& renderer,
                              const std::vector<std::string>& _textures);

    SDL2pp::Texture& getTexture(int index);

    SDL2pp::Texture& getTexture(TextureType type);

    SDL2pp::Texture& getBlockTexture(int index);

    ~TextureContainer();
};

#endif
