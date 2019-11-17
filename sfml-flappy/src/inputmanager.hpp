#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

namespace evansofts {

    class InputManager{
    public:
        InputManager(){}
        ~InputManager(){}

        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
        sf::Vector2i GetMousePosition(sf::RenderWindow& window);
    };

}

#endif