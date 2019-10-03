#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "../game.h"
#include "../component.h"
#include "./transformcomponent.h"

class ColliderComponent : public Component {
public:
    std::string tag;
    SDL_Rect collider;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    TransformComponent* transform;
    static SDL_Texture* boundingBox;


    ColliderComponent(std::string tag, int x, int y, int w, int h){
        this->tag = tag;
        this->collider = SDL_Rect{x, y, w, h};

    }

    ~ColliderComponent() override{

    }


    void initialize() override {
        if(owner->hasComponent<TransformComponent>()) {
            transform = owner->getComponent<TransformComponent>();
            sourceRect = {0, 0, transform->width, transform->height};
            destRect = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    std::string getName() const noexcept override {
        return "ColliderComponent";
    }

    void update(float deltaTime) override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;

        destRect.x = collider.x - Game::camera.x;
        destRect.y = collider.y - Game::camera.y;
    }

    void render(SDL_Renderer* renderer){
        //Debug bounding box
        //TextureManager::Draw(renderer, boundingBox, sourceRect, destRect, SDL_FLIP_NONE);
    }

};



#endif