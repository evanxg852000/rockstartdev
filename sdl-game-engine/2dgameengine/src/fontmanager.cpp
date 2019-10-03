#include "./fontmanager.h"

TTF_Font* FontManager::loadFont(const char* fileName, int fontSize){
    return TTF_OpenFont(fileName, fontSize);
}

void FontManager::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect position){
    SDL_RenderCopy(renderer, texture, NULL, &position);
}