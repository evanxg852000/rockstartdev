#include <sstream>
#include <iostream>
#include <fstream>

#include "./gameoverstate.hpp"
#include "./gamestate.hpp"
#include "./definitions.hpp"

namespace evansofts {

    GameOverState::GameOverState(GameDataRef data, int score): _data(data), _score{score} {
        _highScore = 0;
    }

    void GameOverState::Init(){
        std::fstream file;
        file.open("./assets/score.txt");
        if(file.is_open()){
            while (!file.eof()){
                file >> _highScore;
            }
        }
        
        if(_score > _highScore){
            _highScore = _score;
            file.clear();
            file.seekg(0, file.beg);
            file << _highScore;
        }
        file.close();

        _data->assets.LoadTexture("gameover_bg", "./assets/images/sky.png");
        _data->assets.LoadTexture("gameover_body", "./assets/images/game_over_body.png");
        _data->assets.LoadTexture("gameover_title", "./assets/images/game_over_title.png");
        _data->assets.LoadTexture("bronze_medal", "./assets/images/bronze_medal.png");
        _data->assets.LoadTexture("silver_medal", "./assets/images/silver_medal.png");
        _data->assets.LoadTexture("gold_medal", "./assets/images/gold_medal.png");
        _data->assets.LoadTexture("platinum_medal", "./assets/images/platinum_medal.png");

        _background.setTexture(this->_data->assets.GetTexture("gameover_bg"));
        _gameOverContainer.setTexture(this->_data->assets.GetTexture("gameover_body"));
        _gameOverTitle.setTexture(this->_data->assets.GetTexture("gameover_title"));
        _retryButton.setTexture(this->_data->assets.GetTexture("play_btn"));

        _gameOverContainer.setPosition((_data->window.getSize().x /2)- (_gameOverContainer.getGlobalBounds().width/2),
         (_data->window.getSize().y /2)- (_gameOverContainer.getGlobalBounds().height/2) ); 
        _gameOverTitle.setPosition((_data->window.getSize().x /2)- (_gameOverTitle.getGlobalBounds().width/2),
            _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2));

        _retryButton.setPosition((_data->window.getSize().x /2)- (_retryButton.getGlobalBounds().width/2),
        _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + _retryButton.getGlobalBounds().height * 0.2);

        _scoreText.setFont(_data->assets.GetFont("flappy_font"));
        _scoreText.setString(std::to_string(_score));
        _scoreText.setCharacterSize(56);
        _scoreText.setColor(sf::Color::White);
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width/2, _scoreText.getGlobalBounds().height/2);
        _scoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15);
 
        _highScoreText.setFont(_data->assets.GetFont("flappy_font"));
        _highScoreText.setString(std::to_string(_highScore));
        _highScoreText.setCharacterSize(56);
        _highScoreText.setColor(sf::Color::White);
        _highScoreText.setOrigin(_highScoreText.getGlobalBounds().width/2, _highScoreText.getGlobalBounds().height/2);
        _highScoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78);

        if(_score >= PLATINUM_MEDAL_SCORE) {
            _medal.setTexture(_data->assets.GetTexture("platinum_medal"));
        } else if(_score >= GOLD_MEDAL_SCORE){
            _medal.setTexture(_data->assets.GetTexture("gold_medal"));
        } else if(_score >= SILVER_MEDAL_SCORE) {
            _medal.setTexture(_data->assets.GetTexture("silver_medal"));
        } else {
            _medal.setTexture(_data->assets.GetTexture("bronze_medal"));
        }
        _medal.setPosition(175, 465);
 }

    void GameOverState::HandleInput(){
        sf::Event event;
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type ){
                _data->window.close();
            }

            if(_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window)){
                _data->machine.AddState(StateRef(new GameState(_data)));
            }
        }
    }

    void GameOverState::Update(float dt){

    }

    void GameOverState::Draw(float dt){
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_gameOverContainer);
        _data->window.draw(_gameOverTitle);
        _data->window.draw(_retryButton);

        _data->window.draw(_scoreText);
        _data->window.draw(_highScoreText);
        _data->window.draw(_medal);

        _data->window.display();
    }


}