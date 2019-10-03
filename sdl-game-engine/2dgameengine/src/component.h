#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>
#include <SDL2/SDL.h>


class Entity;

class Component {
public:
    virtual ~Component() = default;
    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual std::string getName() const noexcept = 0;
    void setOwner(Entity* owner) { this->owner = owner; }

protected:
    Entity* owner;
};

#endif