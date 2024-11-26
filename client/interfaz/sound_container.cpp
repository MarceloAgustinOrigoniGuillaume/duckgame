#include "sound_container.h"

SoundContainer::SoundContainer(): backgroundMusic(DATA_PATH "/music/DuckGame-challenging.wav") {
    sounds.emplace(SoundType::JUMP, SDL2pp::Chunk(DATA_PATH "/sounds/jump.mp3"));
    sounds.emplace(SoundType::SHOT, SDL2pp::Chunk(DATA_PATH "/sounds/cowboyPistol.wav"));
    sounds.emplace(SoundType::QUACK, SDL2pp::Chunk(DATA_PATH "/sounds/quack.wav"));
    sounds.emplace(SoundType::LASER, SDL2pp::Chunk(DATA_PATH "/sounds/pewpewLaser.mp3"));
    sounds.emplace(SoundType::PICK_UP, SDL2pp::Chunk(DATA_PATH "/sounds/equip.wav"));
    sounds.emplace(SoundType::ROUND_END, SDL2pp::Chunk(DATA_PATH "/sounds/challengeWin.wav"));
}

SDL2pp::Music& SoundContainer::getBackgroundMusic() { return backgroundMusic; }

SDL2pp::Chunk& SoundContainer::getSound(SoundType type) { return sounds.at(type); }

SoundContainer::~SoundContainer() = default;
