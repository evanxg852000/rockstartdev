#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <typeinfo>

#include <SDL2/SDL.h>

#include "./constants.h"

class EntityManager;
class Component;

class Entity {
public:
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name, LayerType layer);
    virtual ~Entity() = default;
    void update(float deltaTime);
    void render(SDL_Renderer *renderer);
    void destroy();
    bool isActive() const noexcept;

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... args){
        T* component = new T{std::forward<TArgs>(args)...};
        component->setOwner(this);
        components.emplace_back(component);
        componentTypeMap.emplace(&typeid(*component), component);
        component->initialize();
        return *component;
    }

    template<typename T>
    T* getComponent(){
        return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }

    template<typename T>
    bool hasComponent() const {
        return componentTypeMap.find(&typeid(T)) != componentTypeMap.end();
    }

    std::string getName() const noexcept {
        return name;
    }
    void listComponents() const noexcept;

    LayerType getLayerType() const noexcept {
        return layer;
    }

private:
    std::string name;
    bool active;
    LayerType layer;
    EntityManager& manager;
    std::unordered_map<const std::type_info*, Component*> componentTypeMap; 
    std::vector<Component*> components;
};

#endif