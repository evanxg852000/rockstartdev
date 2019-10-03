#ifndef GAME_H
#define GAME_H

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/lua/sol.hpp"
#include "./entitymanager.h"
#include "./assetmanager.h"
#include "./map.h"


class Game {
public:
    Game();
    virtual ~Game();
    bool isRunning() const noexcept;
    void loadLevel(int levelNumber);
    void initialize(uint width, uint height);
    void processInput();
    void update();
    void render();
    void handleCameraMovement();
    void checkCollisions();
    void processNextLevel();
    void processGameOver();
    // void destroy();
    static SDL_Event event;
    static SDL_Rect camera;
    

private:
    bool running;
    int ticksLastFrame;
    SDL_Window *window;
    SDL_Renderer *renderer;
    EntityManager manager;
    AssetManager assetManager;
    Map *map;
    
};

#endif
