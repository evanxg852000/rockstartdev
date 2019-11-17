
#include "./pipe.hpp"



namespace evansofts{

    Pipe::Pipe(GameDataRef data) : _data{data} {
        _landHeight = _data->assets.GetTexture("land").getSize().y - 120;
        _pipeSpawnYOffset = 0;
    }

    void Pipe::SpawnBottomPipe(){
        sf::Sprite sprite(_data->assets.GetTexture("pipe_up"));
        sprite.setPosition(_data->window.getSize().x, 
            _data->window.getSize().y - sprite.getGlobalBounds().height - _pipeSpawnYOffset);
        _pipeSprites.push_back(sprite);
    }

    void Pipe::SpawnTopPipe(){
        sf::Sprite sprite(_data->assets.GetTexture("pipe_down"));
        sprite.setPosition(_data->window.getSize().x, 0 - _pipeSpawnYOffset);
        _pipeSprites.push_back(sprite);
    }

    void Pipe::SpawnInvisiblePipe(){
       sf::Sprite sprite(_data->assets.GetTexture("pipe_up"));
        sprite.setPosition(_data->window.getSize().x, 
            _data->window.getSize().y - sprite.getGlobalBounds().height);
        sprite.setColor(sf::Color(0,0,0,0));
        _pipeSprites.push_back(sprite); 
    }

    void Pipe::SpawnScoringPipe(){
       sf::Sprite sprite(_data->assets.GetTexture("scoring_pipe"));
        sprite.setPosition(_data->window.getSize().x, 0);
        //sprite.setColor(sf::Color(0,0,0,0));
        _scoringSprites.push_back(sprite); 
    }

    void Pipe::MovePipes(float dt){
        std::remove_if(_pipeSprites.begin(), _pipeSprites.end(), [](auto i){ 
            return i.getPosition().x < 0 - i.getGlobalBounds().width; 
        });
        for(auto& pipe : _pipeSprites){
            float movement = PIPE_MOVEMENT_SPEED * dt;
            pipe.move(-movement, 0);
        }

        std::remove_if(_scoringSprites.begin(), _scoringSprites.end(), [](auto i){ 
            return i.getPosition().x < 0 - i.getGlobalBounds().width; 
        });
        for(auto& pipe : _scoringSprites){
            float movement = PIPE_MOVEMENT_SPEED * dt;
            pipe.move(-movement, 0);
        }
        

    }

    void Pipe::DrawPipes(){
        for(auto& pSprite : _pipeSprites) {
            _data->window.draw(pSprite);
        }
    }

    void Pipe::RandomisePipeOffset(){
        _pipeSpawnYOffset = rand() % (_landHeight + 1);
    }

    const std::vector<sf::Sprite>& Pipe::GetSprites() const{
        return _pipeSprites;
    }

    std::vector<sf::Sprite>& Pipe::GetScoringSprites() {
        return _scoringSprites;
    }

}