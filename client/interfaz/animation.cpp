#include "animation.h"

Animation::Animation(const GameContext& context, SoundManager& soundManager):
        animationBuilders(), soundManager(soundManager), frameTicks(0) {
    for (int i = 1; i <= static_cast<int>(context.cantidadjugadores); i++) {
        animationBuilders.emplace(i, AnimationBuilder());
    }
}

void Animation::updateFrame() { frameTicks = SDL_GetTicks(); }

void Animation::updateSprite(const MatchDto& matchDto) {
    for (const PlayerDTO& player: matchDto.players) {
        AnimationBuilder* builder = getAnimationBuilder(player.id);
        if (builder) {
            if (player.is_alive) {
                updatePlayerAnimation(*builder, player);

                for (const TypeDoingAction& action: player.doing_actions) {
                    updateDoingActionAnimation(*builder, player, action);
                }
            } else {
                setBuilder(*builder, STARTING_SPRITE_X + SPRITE_SIZE, LAY_DOWN_SPRITE_Y);
            }
        }
    }
}

void Animation::updateDoingActionAnimation(AnimationBuilder& builder, const PlayerDTO& player, const TypeDoingAction& action) {
    switch (action) {
        case TypeDoingAction::SHOOTING:
        case TypeDoingAction::SHOOTING_UP:
            std::cout << "PLAYER [" << player.id << "]: SHOOTING/UP" << std::endl;
            if (player.weapon == TypeWeapon::PEW_PEW_LASER) {
                soundManager.playSound(SoundType::LASER);
            } else {
                soundManager.playSound(SoundType::SHOT);
            }
            builder.doingActionSpriteX = 0;  // cuando se envien bien las acciones
            break;
        case TypeDoingAction::DAMAGED:
            std::cout << "PLAYER [" << player.id << "]: DAMAGED" << std::endl;
            soundManager.playSound(SoundType::QUACK);
            break;
        case TypeDoingAction::PICK_UP:
            std::cout << "PLAYER [" << player.id << "]: PICK UP" << std::endl;
            soundManager.playSound(SoundType::PICK_UP);
            break;
        case TypeDoingAction::NONE:
            break;
    }
}

AnimationBuilder* Animation::getAnimationBuilder(int playerId) {
    auto it = animationBuilders.find(playerId);
    if (it != animationBuilders.end()) {
        return &it->second;
    }
    return nullptr;
}

void Animation::setBuilder(AnimationBuilder& builder, int spriteX, int spriteY, bool facingLeft) {
    builder.spriteX = spriteX;
    builder.spriteY = spriteY;
    builder.facingLeft = facingLeft;
}

void Animation::setBuilder(AnimationBuilder& builder, int spriteX, int spriteY) {
    builder.spriteX = spriteX;
    builder.spriteY = spriteY;
}

void Animation::updatePlayerAnimation(AnimationBuilder& builder, const PlayerDTO& player) {
    switch (player.move_action) {
        case TypeMoveAction::MOVE_RIGHT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                                           RUNNING_ANIMATION_FRAMES)),
                       STARTING_SPRITE_Y, false);
            break;
        case TypeMoveAction::MOVE_LEFT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                                           RUNNING_ANIMATION_FRAMES)),
                       STARTING_SPRITE_Y, true);
            break;
        case TypeMoveAction::AIR_NEUTRAL:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                                           JUMPING_ANIMATION_FRAMES)),
                       JUMPING_SPRITE_Y);
            soundManager.playSound(SoundType::JUMP);
            break;
        case TypeMoveAction::AIR_RIGHT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                                           JUMPING_ANIMATION_FRAMES)),
                       JUMPING_SPRITE_Y, false);
            soundManager.playSound(SoundType::JUMP);
            break;
        case TypeMoveAction::AIR_LEFT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                                           JUMPING_ANIMATION_FRAMES)),
                       JUMPING_SPRITE_Y, true);
            soundManager.playSound(SoundType::JUMP);
            break;
        case TypeMoveAction::FLAP_NEUTRAL:
            setBuilder(builder, (STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET),
                       FLAPPING_SPRITE_Y);
            break;
        case TypeMoveAction::FLAP_RIGHT:
            setBuilder(builder, (STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET),
                       FLAPPING_SPRITE_Y, false);
            break;
        case TypeMoveAction::FLAP_LEFT:
            setBuilder(builder, (STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET),
                       FLAPPING_SPRITE_Y, true);
            break;
        case TypeMoveAction::STAY_DOWN:
            setBuilder(builder, STARTING_SPRITE_X, LAY_DOWN_SPRITE_Y);
            break;
        case TypeMoveAction::NONE:
            setBuilder(builder, STARTING_SPRITE_X, STARTING_SPRITE_Y);
            break;
    }
}

bool Animation::isFacingLeft(int playerId) {
    AnimationBuilder* builder = getAnimationBuilder(playerId);
    if (builder) {
        return builder->facingLeft;
    }
    return false;
}

int Animation::getSpriteX(int playerId) {
    AnimationBuilder* builder = getAnimationBuilder(playerId);
    if (builder) {
        return builder->spriteX;
    }
    return 0;
}

int Animation::getSpriteY(int playerId) {
    AnimationBuilder* builder = getAnimationBuilder(playerId);
    if (builder) {
        return builder->spriteY;
    }
    return 0;
}

float Animation::getIndicatorSprite(float width) {
    return width * ((frameTicks / INDICATOR_ANIMATION_SPEED) % INDICATOR_ANIMATION_FRAMES);
}

Animation::~Animation() = default;
