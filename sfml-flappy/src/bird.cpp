
#include "./bird.hpp"
#include "./definitions.hpp"

namespace evansofts {

    Bird::Bird(GameDataRef data): _data{data} {
        _animationIterator = 0;
        _animationFrames.push_back(data->assets.GetTexture("bird_01"));
        _animationFrames.push_back(data->assets.GetTexture("bird_02"));
        _animationFrames.push_back(data->assets.GetTexture("bird_03"));
        _animationFrames.push_back(data->assets.GetTexture("bird_04"));

        _sprite.setTexture(_animationFrames.at(_animationIterator));
        _sprite.setPosition((_data->window.getSize().x / 4) - (_sprite.getGlobalBounds().width / 2),
         (_data->window.getSize().y / 2) - (_sprite.getGlobalBounds().height / 2) );

        _state = State::Still;
        sf::Vector2f origin = sf::Vector2f(_sprite.getGlobalBounds().width/ 2, _sprite.getGlobalBounds().height/ 2);
        _sprite.setOrigin(origin);
        _rotation = 0;
    }

    void Bird::Draw(){
        _data->window.draw(_sprite);
    }

    void Bird::Animate(float dt){
        if(_clock.getElapsedTime().asSeconds()> BIRD_ANIMATION_DURATION /_animationFrames.size()){
            _animationIterator = (_animationIterator + 1) % _animationFrames.size();
            _sprite.setTexture(_animationFrames.at(_animationIterator));
            _clock.restart();
        }
    }

    void Bird::Update(float dt){
        if(_state == State::Falling){
            _sprite.move(0, GRAVITY * dt);
            _rotation += (_rotation >= 25.0f)? 0.0f :  ROTATION_SPEED * dt;
            _sprite.setRotation(_rotation);
        } else if (_state == State::Flying){
            _sprite.move(0, -FLYING_SPEED * dt);
            _rotation -= (_rotation <= -25.0f)? 0.0f :  ROTATION_SPEED * dt;
            _sprite.setRotation(_rotation);
        }

        if(_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION) {
            _movementClock.restart();
            _state = State::Falling;
        }

    }

    void Bird::Tap(){
        _movementClock.restart();
        _state = State::Flying;
    }

    const sf::Sprite& Bird::GetSprite() const{
        return _sprite;
    }

}