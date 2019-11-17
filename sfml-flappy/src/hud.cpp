
#include <string>

#include "./hud.hpp"

namespace evansofts {

    Hud::Hud(GameDataRef data): _data{data} {
        _scoreText.setFont(_data->assets.GetFont("flappy_font"));
        _scoreText.setString("0");
        _scoreText.setCharacterSize(128);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width/2, _scoreText.getGlobalBounds().height/2);
        _scoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y / 7);
    }

    void Hud::Draw(){
        _data->window.draw(_scoreText);
    }

    void Hud::UpdateScore(int score) {
        _scoreText.setString(std::to_string(score));
    }

}