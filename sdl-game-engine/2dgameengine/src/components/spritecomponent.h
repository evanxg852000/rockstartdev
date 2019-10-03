#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../component.h"
#include "../texturemanager.h"
#include "../assetmanager.h"
#include "./transformcomponent.h"
#include "../animation.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(SDL_Texture* texture): texture{texture} {
        animated = false;
        fixed = false;
    }

    SpriteComponent(SDL_Texture* texture, int frames, int speed, bool hasDirection, bool isFixed): texture{texture} {
        animated = true;
        numFrames = frames;
        animationSpeed = speed;
        fixed = isFixed;
        if(hasDirection){
            Animation downAnimation = Animation{0, numFrames, speed};
            Animation rightAnimation = Animation{1, numFrames, speed};
            Animation leftAnimation = Animation{2, numFrames, speed};
            Animation upAnimation = Animation{3, numFrames, speed};
            
            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("UpAnimation", upAnimation);

            animationIndex = 0;
            currentAnimationName = "DownAnimation";
        } else {
            Animation singleAnim = Animation{0, numFrames, speed};
            animations.emplace("SingleAnimation", singleAnim);
            animationIndex = 0;
            currentAnimationName = "SingleAnimation"; 
        }

        play(currentAnimationName);
    }

    ~SpriteComponent() override {
    }


    void play(std::string animationName){
        numFrames = animations[animationName].numFrames;
        animationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimationName = animationName;
    }

    void initialize() override {
        transform = owner->getComponent<TransformComponent>();
        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = transform->width;
        sourceRect.h = transform->height;
    }

    void update(float deltaTime) override {
        if(animated){
            sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
        }
        sourceRect.y = animationIndex * transform->height;
        destRect.x = transform->position.x - (fixed? 0 : Game::camera.x);
        destRect.y = transform->position.y - (fixed? 0 : Game::camera.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void render(SDL_Renderer* renderer) override {
        TextureManager::Draw(renderer, texture, sourceRect, destRect, spriteFlip);
    }
    
    std::string getName() const noexcept override {
        return "SpriteComponent";
    }
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_RendererFlip spriteFlip{SDL_FLIP_NONE};
    bool animated;
    int numFrames;
    int animationSpeed;
    bool fixed;
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned int animationIndex = 0;

};


#endif
