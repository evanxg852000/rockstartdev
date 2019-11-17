#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include <SFML/Graphics.hpp>

#include "./state.hpp"
#include "./game.hpp"

namespace evansofts {

    class SplashState: public State {
    public:
        SplashState(GameDataRef data);

        void Init();

        void HandleInput() override;
        void Update(float dt) override;
        void Draw(float dt) override;
    
    private:
        GameDataRef _data;
        sf::Clock _clock;
        sf::Sprite _background;
    };

}


#endif