#ifndef BIRD_H
#define BIRD_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "./game.hpp"

namespace evansofts {



    class Bird {
    public:
        enum class State{
            Still = 1,
            Falling,
            Flying
        };

        Bird(GameDataRef data);
        void Draw();
        void Animate(float dt);
        void Update(float dt);
        void Tap();
        const sf::Sprite& GetSprite() const;
    
    private:
        GameDataRef _data;
        sf::Sprite _sprite;
        std::vector<sf::Texture> _animationFrames;
        uint _animationIterator;
        sf::Clock _clock;
        sf::Clock _movementClock;
        State _state;
        float _rotation;
    };

}

#endif