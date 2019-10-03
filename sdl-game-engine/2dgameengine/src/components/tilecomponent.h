#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "../../lib/glm/glm.hpp"

#include "../component.h"
#include "./transformcomponent.h"
#include "./spritecomponent.h"
#include "../game.h"
#include "../texturemanager.h"

class TileComponent : public Component {
public:
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    glm::vec2 position;

    TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, SDL_Texture* texture) {
        sourceRect.x = srcRectX;
        sourceRect.y = srcRectY;
        sourceRect.w = tileSize;
        sourceRect.h = tileSize;
        destinationRect.x = x;
        destinationRect.y = y;
        destinationRect.w = tileSize * tileScale;
        destinationRect.h = tileSize * tileScale;

        position.x = x;
        position.y = y;
        this->texture = texture;
    }

    ~TileComponent() override {
    }

    std::string getName() const noexcept override {
        return "TileComponent";
    }

    void initialize() override {

    }

    void update(float deltaTime) override {
        destinationRect.x = position.x - Game::camera.x;
        destinationRect.y = position.y - Game::camera.y;
    }

    void render(SDL_Renderer* renderer) override {
        TextureManager::Draw(renderer, texture, sourceRect, destinationRect, SDL_FLIP_NONE);
    }

};

#endif