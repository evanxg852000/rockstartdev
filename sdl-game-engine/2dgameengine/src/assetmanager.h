#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <unordered_map>
#include <string> 
#include <SDL2/SDL_ttf.h>

#include "./entitymanager.h"
#include "./fontmanager.h"
#include "./texturemanager.h"


class AssetManager {
public:
    AssetManager() = default;
    AssetManager(SDL_Renderer* renderer, EntityManager& manager);
    virtual ~AssetManager();
    void clearData();
    void addTexture(std::string key, const char* filename);
    SDL_Texture* getTexture(std::string key);
    void addFont(std::string key, const char* filename, int fontSize);
    TTF_Font* getFont(std::string key);
private:
    SDL_Renderer* renderer;
    EntityManager manager;
    std::unordered_map<std::string, SDL_Texture*> textures;
    std::unordered_map<std::string, TTF_Font*> fonts;
};

#endif