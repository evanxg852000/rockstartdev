#include <sstream>
#include <iostream>

#include "./splashstate.hpp"
#include "./mainmenustate.hpp"
#include "./definitions.hpp"

namespace evansofts {

    SplashState::SplashState(GameDataRef data): _data(data) {

    }

    void SplashState::Init(){
        _data->assets.LoadTexture("splash_bg", "./assets/images/splash_background.png");
        _background.setTexture(this->_data->assets.GetTexture("splash_bg"));
    }

    void SplashState::HandleInput(){
        sf::Event event;
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type ){
                _data->window.close();
            }
        }
    }

    void SplashState::Update(float dt){
        if(_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME ){
            _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
        }
    }

    void SplashState::Draw(float dt){
        _data->window.clear();
        _data->window.draw(_background);

        _data->window.display();
    }


}