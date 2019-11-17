#ifndef LAND_H
#define LAND_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "./game.hpp"

namespace evansofts {
    class Land {
    public:
        Land(GameDataRef data);
        void MoveLand(float dt);
        void DrawLand();
        const std::vector<sf::Sprite>& GetSprites() const; 

    private:
        GameDataRef _data;
        std::vector<sf::Sprite> _landSprites;
    };

}

#endif