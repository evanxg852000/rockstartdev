#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "../component.h"
#include "../entity.h"
#include "../../lib/glm/glm.hpp"


class TransformComponent: public Component {
public:
    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s){
        position = glm::vec2{posX, posY};
        velocity = glm::vec2{velX, velY};
        width = w;
        height = h;
        scale = s;
    }

    void initialize() override {
    }

    void update(float deltaTime) override {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }

    void render(SDL_Renderer *renderer) override {
        // SDL_Rect transformRect{ (int)position.x, (int)position.y, width, height};
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // SDL_RenderFillRect(renderer, &transformRect);
    }

    ~TransformComponent() override {
    }

    std::string getName() const noexcept override{
        return "TransformComponent";
    }

//private:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;
};

#endif
