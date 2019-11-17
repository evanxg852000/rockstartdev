#include "./land.hpp"
#include "definitions.hpp"

namespace evansofts {

    Land::Land(GameDataRef data): _data{data} {
        sf::Sprite sprite(_data->assets.GetTexture("land"));
        sf::Sprite sprite2(_data->assets.GetTexture("land"));
        sprite.setPosition(0, _data->window.getSize().y- sprite.getGlobalBounds().height + 120);
        sprite2.setPosition(sprite.getGlobalBounds().width, _data->window.getSize().y- sprite.getGlobalBounds().height + 120);

        _landSprites.push_back(sprite);
        _landSprites.push_back(sprite2);
    }

    void Land::MoveLand(float dt){
        for(auto& land : _landSprites){
            float movement = PIPE_MOVEMENT_SPEED * dt;
            land.move(-movement, 0);
            if(land.getPosition().x < 0- land.getGlobalBounds().width){
                land.setPosition(_data->window.getSize().x, land.getPosition().y);  
            }
        }
    }

    void Land::DrawLand(){
        for(auto& land : _landSprites){
            _data->window.draw(land);
        }

    }


    const std::vector<sf::Sprite>& Land::GetSprites() const{
        return _landSprites;
    }
}