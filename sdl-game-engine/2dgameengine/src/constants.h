#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

enum class CollisionType{
    None,
    PlayerEnemy,
    PlayerProjectile,
    EnemyProjectile,
    PlayerVegetegation,
    PlayerLevelComplete
};

enum class LayerType {
    TileMap = 0,
    Vegetation,
    Enemy,
    Obstacle,
    Player,
    Projectile,
    Ui
};

const unsigned int NUM_LAYERS = 7;

const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color WHITE_GREEN = {0, 255, 0, 255};

#endif