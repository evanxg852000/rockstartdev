#ifndef KEYBOARD_COMPONENT_H
#define KEYBOARD_COMPONENT_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "../component.h"
#include "./transformcomponent.h"
#include "./spritecomponent.h"
#include "../game.h"

class KeyboardComponent : public Component {
public:
    std::string upKey;
    std::string rightKey;
    std::string downKey;
    std::string leftKey;
    std::string shootKey;
    TransformComponent *transform;
    SpriteComponent *sprite;

    KeyboardComponent(){

    }

    KeyboardComponent(std::string up, std::string right, std::string down, 
    std::string left, std::string shoot){
        upKey = getSDLKeyStringCode(up);
        rightKey = getSDLKeyStringCode(right);
        downKey = getSDLKeyStringCode(down);
        leftKey = getSDLKeyStringCode(left);
        shootKey = getSDLKeyStringCode(shoot);
    }
    
    ~KeyboardComponent() override {};

    std::string getSDLKeyStringCode(std::string key){
        if(key.compare("up") == 0) return "1073741906"; 
        if(key.compare("right") == 0) return "1073741903"; 
        if(key.compare("down") == 0) return "1073741905"; 
        if(key.compare("left") == 0) return "1073741904"; 
        if(key.compare("space") == 0) return "32"; 
        return std::to_string(static_cast<int>(key[0]));
    }

    void initialize() override {
        transform = owner->getComponent<TransformComponent>();
        sprite = owner->getComponent<SpriteComponent>();
    }

    std::string getName() const noexcept override {
        return "KeyboardComponent";
    }

    void update(float deltaTime) override {
        if(Game::event.type == SDL_KEYDOWN){
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);
            
            if(keyCode.compare(upKey) == 0){
                transform->velocity.y = -60;
                transform->velocity.x = 0;
                sprite->play("UpAnimation");
            }
            if(keyCode.compare(rightKey) == 0){
                transform->velocity.y = 0;
                transform->velocity.x = 60;
                sprite->play("RightAnimation");
            }
            if(keyCode.compare(downKey) == 0){
                transform->velocity.y = 60;
                transform->velocity.x = 0;
                sprite->play("DownAnimation");
            }
            if(keyCode.compare(leftKey) == 0){
                transform->velocity.y = 0;
                transform->velocity.x = -60;
                sprite->play("LeftAnimation");
            }
            if(keyCode.compare(shootKey) == 0){
                //TODO: fire missile
            }
        }

        if(Game::event.type == SDL_KEYUP) {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);

            if(keyCode.compare(upKey) == 0){
                transform->velocity.y = 0;
            }
            if(keyCode.compare(rightKey) == 0){
                transform->velocity.x = 0;
            }
            if(keyCode.compare(downKey) == 0){
                transform->velocity.y = 0;
            }
            if(keyCode.compare(leftKey) == 0){
                transform->velocity.x = 0;
            }
        }
    }

    void render(SDL_Renderer* renderer) override{

    }

};




#endif