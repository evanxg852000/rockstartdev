#include <sstream>
#include <iostream>

#include "./gamestate.hpp"
#include "./definitions.hpp"
#include "./gameoverstate.hpp"

namespace evansofts {

    GameState::GameState(GameDataRef data): _data(data) {

    }

    void GameState::Init(){
        hitSb.loadFromFile("./assets/audio/hit.wav");
        wingSb.loadFromFile("./assets/audio/wing.wav");
        pointSb.loadFromFile("./assets/audio/point.wav");
    
        hitSound.setBuffer(hitSb);
        wingSound.setBuffer(wingSb);
        pointSound.setBuffer(pointSb);

        _data->assets.LoadTexture("game_bg", "./assets/images/sky.png");
        _background.setTexture(this->_data->assets.GetTexture("game_bg"));
        _data->assets.LoadTexture("pipe_up", "./assets/images/pipe_up.png");
        _data->assets.LoadTexture("pipe_down", "./assets/images/pipe_down.png");
        _data->assets.LoadTexture("scoring_pipe", "./assets/images/invisible_scoring_pipe.png");
        _data->assets.LoadTexture("land", "./assets/images/land.png");

        _data->assets.LoadTexture("bird_01", "./assets/images/bird_01.png");
        _data->assets.LoadTexture("bird_02", "./assets/images/bird_02.png");
        _data->assets.LoadTexture("bird_03", "./assets/images/bird_03.png");
        _data->assets.LoadTexture("bird_04", "./assets/images/bird_04.png");

        _data->assets.LoadFont("flappy_font", "./assets/fonts/flappy_font.ttf");
        
        pipe = std::make_unique<Pipe>(_data);
        land = std::make_unique<Land>(_data);
        bird = std::make_unique<Bird>(_data);
        flash = std::make_unique<Flash>(_data);
        hud = std::make_unique<Hud>(_data);

        _score = 0;
        hud->UpdateScore(_score);
        _state = GameStates::Ready;
    }

    void GameState::HandleInput(){
        sf::Event event;
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type ){
                _data->window.close();
            }

            if(_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window)){
                if(_state != GameStates::GameOver){
                    _state = GameStates::Playing;
                    bird->Tap();
                    wingSound.play();
                }
            }

        }
    }

    void GameState::Update(float dt){
        if(_state != GameStates::GameOver){
            bird->Animate(dt);
            land->MoveLand(dt);
        }
        if(_state == GameStates::Playing){
            pipe->MovePipes(dt);
            if(_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY){
                pipe->RandomisePipeOffset(); 

                pipe->SpawnInvisiblePipe();
                pipe->SpawnBottomPipe();
                pipe->SpawnTopPipe();
                pipe->SpawnScoringPipe();
            
                _clock.restart();
            }
            
            bird->Update(dt);
            
            auto& _lands = land->GetSprites();
            for(auto& landItem : _lands){
                if(collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landItem, 1.0f)){
                    _state = GameStates::GameOver;
                    _clock.restart();
                    hitSound.play();
                }
            }

            auto& _pipes = pipe->GetSprites();
            for(auto& pipeItem : _pipes){
                if(collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeItem, 1.0f)){
                    _state = GameStates::GameOver;
                    _clock.restart();
                    hitSound.play();
                }
            }

            if(_state == GameStates::Playing){
                auto& _scoringPipes = pipe->GetScoringSprites();
                auto it = _scoringPipes.begin();
                while (it != _scoringPipes.end()) {
                    if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, *it, 1.0f)) {
                        it = _scoringPipes.erase(it);
                        _score += 1;
                        hud->UpdateScore(_score);
                        pointSound.play();

                    } else {
                        ++it;
                    }
                }
            }

        }

        if(_state == GameStates::GameOver){
            flash->Show(dt);
            if(_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APEARS){
                _data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
            }
        }
    }

    void GameState::Draw(float dt){
        _data->window.clear();
        _data->window.draw(_background);

        pipe->DrawPipes();
        land->DrawLand();
        bird->Draw();
        flash->Draw();
        hud->Draw();

        _data->window.display();
    }


}