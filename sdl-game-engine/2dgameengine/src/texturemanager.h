#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {
public:
    TextureManager() = default;
    virtual ~TextureManager() = default;
    static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* fileName);
    static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

#endif