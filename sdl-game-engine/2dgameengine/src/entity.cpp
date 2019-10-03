#include <iostream>
#include <typeinfo>

#include "./entity.h"
#include "./component.h"
#include "./entitymanager.h"


Entity::Entity(EntityManager& manager): manager{manager} {
    this->active = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer)
 : manager{manager}, name{name}, layer{layer} {
    this->active = true;
}

void Entity::update(float deltaTime) {
    for(auto& component: components){
        component->update(deltaTime);
    }
}

void Entity::render(SDL_Renderer *renderer) {
    for(auto& component: components){
        component->render(renderer);
    }
}

void Entity::destroy() {
    this->active = false;
}

bool Entity::isActive() const noexcept{
    return this->active;
}

void Entity::listComponents() const noexcept {
    for(auto& component : components){
        // typeid(component).name() yield pointer type P9Component 
        std::cout << "\t" << "Component<" <<  component->getName() << ">" << std::endl;
    }
}