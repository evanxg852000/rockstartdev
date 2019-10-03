#ifndef PROJECTILE_EMITTER_COMPONENT
#define PROJECTILE_EMITTER_COMPONENT


#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "../../lib/glm/glm.hpp"
#include "../game.h"
#include "../component.h"
#include "../entitymanager.h"
#include "./transformcomponent.h"

class ProjectileEmitterComponent : public Component {
public:
    TransformComponent* transform;
    glm::vec2 origin;
    int speed;
    int range;
    float angleRad;
    bool shouldLoop;

    ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop){
        this->speed = speed;
        this->range = range;
        this->shouldLoop = shouldLoop;
        this->angleRad =  glm::radians(static_cast<float>(angleDeg));
    }

    ~ProjectileEmitterComponent() override {

    }

    std::string getName() const noexcept override {
        return "ProjectileEmitterComponent";
    }

    void initialize() override {
        transform = owner->getComponent<TransformComponent>();
        origin = glm::vec2{transform->position.x, transform->position.y};
        transform->velocity = glm::vec2{ glm::cos(angleRad)* speed, glm::sin(angleRad) * speed };
    }

    void update(float deltaTime) override {
        if(glm::distance(transform->position, origin) > range ) {
            if(shouldLoop){
                transform->position.x = origin.x;
                transform->position.y = origin.y;
            } else {
                owner->destroy();
            }
        }
    }

    void render(SDL_Renderer* renderer) override{

    }

};


#endif