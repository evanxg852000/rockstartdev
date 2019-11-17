#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <SFML/Graphics.hpp>

#include "./state.hpp"
#include "./game.hpp"

namespace evansofts {

    class MainMenuState: public State {
    public:
        MainMenuState(GameDataRef data);

        void Init();

        void HandleInput() override;
        void Update(float dt) override;
        void Draw(float dt) override;
    
    private:
        GameDataRef _data;
        
        sf::Sprite _background;
        sf::Sprite _title;
        sf::Sprite _playBtn;
    };

}


#endif