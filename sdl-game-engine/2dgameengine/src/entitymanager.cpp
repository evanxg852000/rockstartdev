#include <iostream>
#include <algorithm>

#include "./entitymanager.h"
#include "./collision.h"
#include "./components/collidercomponent.h"

void EntityManager::clearData(){
    for(auto& entity : entities){
        entity->destroy();
    }
}

void EntityManager::update(float deltaTime) {
    for(auto& entity : entities){
        entity->update(deltaTime);
    }
    std::remove_if(entities.begin(), entities.end(), [&](auto entity) {return !entity->isActive(); });
}

void EntityManager::render(SDL_Renderer *renderer) {
    for (auto layerNum = 0; layerNum < NUM_LAYERS; layerNum++){
        auto items = this->getEntitiesByLayer(static_cast<LayerType>(layerNum));
        for(auto& entity : items){
            entity->render(renderer);
        }  
    }
    // for(auto& entity : entities){
    //     entity->render(renderer);
    // }
}

bool EntityManager::hasNoEntity() const noexcept{
    return entities.size() == 0;
}

Entity& EntityManager::addEntity(std::string entityName, LayerType layer){
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

Entity& EntityManager::getEntity(std::string entityName){
    for(auto& entity : entities){
        if(entity->getName() == entityName)
            return *entity;
    }
}

CollisionType EntityManager::checkEntityCollisions() const{
    for(auto& thisEntity : entities) {
        if(!thisEntity->hasComponent<ColliderComponent>()) 
            continue;
        ColliderComponent* thisCollider = thisEntity->getComponent<ColliderComponent>();
        for(auto& thatEntity : entities){
            if(!thatEntity->hasComponent<ColliderComponent>() || thisEntity->getName() == thatEntity->getName() ) 
                continue; 
            ColliderComponent* thatCollider = thatEntity->getComponent<ColliderComponent>();

            if(Collision::checkRectangleCollision(thisCollider->collider, thatCollider->collider)) {
                if(thisCollider->tag == "PLAYER" && thatCollider->tag == "ENEMY")
                    return CollisionType::PlayerEnemy;
                
                if(thisCollider->tag == "PLAYER" && thatCollider->tag == "PROJECTILE")
                    return CollisionType::PlayerProjectile;

                if(thisCollider->tag == "ENEMY" && thatCollider->tag == "FRIENDLY_PROJECTILE")
                    return CollisionType::EnemyProjectile;

                if(thisCollider->tag == "PLAYER" && thatCollider->tag == "LEVEL_COMPLETE")
                    return CollisionType::PlayerLevelComplete;
            }
        }
    }
    return CollisionType::None;
}

std::vector<Entity*> EntityManager::getEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::getEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> out;
    std::copy_if(entities.begin(), entities.end(), std::back_inserter(out), [&](auto entity) { return entity->getLayerType() == layer; });
    return out;
}

unsigned int EntityManager::getEntityCount() const noexcept{
    return entities.size();
}

void EntityManager::listEntities() const noexcept {
    for(auto& entity: entities){
        std::cout << "Entity Name:" << entity->getName() << std::endl;
        entity->listComponents();
    }
}