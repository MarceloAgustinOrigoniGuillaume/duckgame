#include "camera.h"

Camera::Camera(): x(0), y(0), zoom(1.0f) {}

void Camera::updateZoom(int boxWidth, int boxHeight) {
    float zoomX = static_cast<float>(SCREEN_WIDTH) / (boxWidth + PADDING);
    float zoomY = static_cast<float>(SCREEN_HEIGHT) / (boxHeight + PADDING);

    // this is necessary to fit the entire group of players in the screen
    zoom = std::min(zoomX, zoomY);
}

void Camera::updatePosition(int minX, int minY, int boxWidth, int boxHeight) {
    x = minX + boxWidth / 2 - (SCREEN_WIDTH / 2) / zoom;
    y = minY + boxHeight / 2 - (SCREEN_HEIGHT / 2) / zoom;
}

void Camera::update(const MatchDto& matchDto) {
    int firstPlayerX = matchDto.players[0].pos.x;
    int firstPlayerY = matchDto.players[0].pos.y;

    int minX = firstPlayerX;
    int maxX = firstPlayerX;
    int minY = firstPlayerY;
    int maxY = firstPlayerY;

    for (const PlayerDTO& player: matchDto.players) {
        if (player.pos.x < minX)
            minX = player.pos.x;
        if (player.pos.x > maxX)
            maxX = player.pos.x;
        if (player.pos.y < minY)
            minY = player.pos.y;
        if (player.pos.y > maxY)
            maxY = player.pos.y;
    }

    // bounding box dimensions
    int boxWidth = maxX - minX;
    int boxHeight = maxY - minY;

    updateZoom(boxWidth, boxHeight);

    updatePosition(minX, minY, boxWidth, boxHeight);
}

int Camera::getScreenX(int playerX) { return static_cast<int>((playerX - x) * zoom); }

int Camera::getScreenY(int playerY) { return static_cast<int>((playerY - y) * zoom); }

int Camera::getScaledSize(int size) { return static_cast<int>(size * zoom); }

int Camera::backgroundScaledSize(int size) { return static_cast<int>(size / zoom); }

Camera::~Camera() = default;
