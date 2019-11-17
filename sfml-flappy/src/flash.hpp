#ifndef FLASH_H
#define FLASH_H

#include <SFML/Graphics.hpp>

#include "./game.hpp"
#include "./definitions.hpp"

namespace evansofts {
    class Flash{
    public: 
        Flash(GameDataRef data);
        void Show(float dt);
        void Draw();
    
    private:
        GameDataRef _data;
        sf::RectangleShape _shape;
        bool _flashOn;
    };
}


#endif