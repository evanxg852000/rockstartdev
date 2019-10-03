#include <iostream>

#include "./texturemanager.h"

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* fileName) {
    SDL_Surface* surface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, texture, &src, &dest, 0.0, 0, flip);
}
