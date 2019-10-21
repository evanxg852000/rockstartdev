#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <string>
#include <optional>

#include <SDL2/SDL.h>

#include "./entity.h"
#include "./component.h"


class EntityManager {
public:
    EntityManager() = default;
    virtual ~EntityManager() = default;
    void clearData();
    void update(float deltaTime);
    void render(SDL_Renderer *renderer);
    bool hasNoEntity() const noexcept;
    Entity& addEntity(std::string entityName, LayerType layer);
    Entity* getEntity(std::string entityName);
    CollisionType checkEntityCollisions() const;
    std::vector<Entity*> getEntities() const;
    std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
    unsigned int getEntityCount() const noexcept;
    void listEntities() const noexcept;

private:
    std::vector<Entity*> entities;

};

#endif