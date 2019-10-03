#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontManager {
public:
    static TTF_Font* loadFont(const char* fileName, int fontSize);
    static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect position);
};

#endif