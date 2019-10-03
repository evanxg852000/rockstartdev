#include "./assetmanager.h"

AssetManager::AssetManager(SDL_Renderer* renderer, EntityManager& manager)
    : renderer{renderer}, manager{manager} {
    
}

AssetManager::~AssetManager(){
    this->clearData();
}

void AssetManager::clearData() {
    for(auto& kv : textures)
        SDL_DestroyTexture(kv.second);
    for(auto& kv : fonts)
        TTF_CloseFont(kv.second);
    
    textures.clear();
    fonts.clear();
}

void AssetManager::addTexture(std::string key, const char* fileName){
    textures.emplace(key, TextureManager::LoadTexture(renderer, fileName));
}

SDL_Texture* AssetManager::getTexture(std::string key){
    return textures[key];
}

void AssetManager::addFont(std::string key, const char* fileName, int fontSize){
    fonts.emplace(key, FontManager::loadFont(fileName, fontSize));
}

TTF_Font* AssetManager::getFont(std::string key){
    return fonts[key];
}