#include <sstream>
#include <iostream>

#include "./mainmenustate.hpp"
#include "./gamestate.hpp"
#include "./definitions.hpp"

namespace evansofts {

    MainMenuState::MainMenuState(GameDataRef data): _data(data) {

    }

    void MainMenuState::Init(){
        _data->assets.LoadTexture("mainmenu_bg", "./assets/images/sky.png");
        _data->assets.LoadTexture("mainmenu_title", "./assets/images/title.png");
        _data->assets.LoadTexture("play_btn", "./assets/images/play_button.png");

        _background.setTexture(this->_data->assets.GetTexture("mainmenu_bg"));
        _title.setTexture(this->_data->assets.GetTexture("mainmenu_title"));
        _playBtn.setTexture(this->_data->assets.GetTexture("play_btn"));

        _title.setPosition((SCREEN_WIDTH/2)- (_title.getGlobalBounds().width / 2), 
            _title.getGlobalBounds().height / 2);
        _playBtn.setPosition((SCREEN_WIDTH/2)- (_playBtn.getGlobalBounds().width / 2), 
            (SCREEN_HEIGHT/2) - (_playBtn.getGlobalBounds().height / 2));
    }

    void MainMenuState::HandleInput(){
        sf::Event event;
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type ){
                _data->window.close();
            }

            if(_data->input.IsSpriteClicked(_playBtn, sf::Mouse::Left, _data->window)){
                _data->machine.AddState(StateRef(new GameState(_data)), true);
            }
        }
    }

    void MainMenuState::Update(float dt){

    }

    void MainMenuState::Draw(float dt){
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_title);
        _data->window.draw(_playBtn);

        _data->window.display();
    }


}