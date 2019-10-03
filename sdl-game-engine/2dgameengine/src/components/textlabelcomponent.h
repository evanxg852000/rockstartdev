#ifndef TEXT_LABEL_COMPONENT
#define TEXT_LABEL_COMPONENT

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../game.h"
#include "../component.h"
#include "../fontmanager.h"
#include "../assetmanager.h"
#include "../entitymanager.h"

class TextLabelComponent : public Component {
private:
    SDL_Rect position;
    std::string text;
    std::string fontFamily;
    SDL_Color color;
    SDL_Texture* texture;

public:
    TextLabelComponent(SDL_Renderer* renderer, TTF_Font* font, int x, int y, std::string text, std::string fontFamily, const SDL_Color& color) {
        this->position.x = x;
        this->position.y = y;
        this->text = text;
        this->fontFamily = fontFamily;
        this->color = color;
        setLabelText(renderer, font, text, fontFamily);
    }

    void setLabelText(SDL_Renderer* renderer, TTF_Font* font, std::string text, std::string fontFamily){
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    }

    ~TextLabelComponent() override{

    }

    std::string getName() const noexcept override {
        return "TextLabelComponent";
    }

    void initialize() override {

    }

    void update(float deltaTime) override {

    }

    void render(SDL_Renderer* renderer){
        FontManager::Draw(renderer, texture, position);
    }

};

#endif