#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "./state.hpp"
#include "./game.hpp"
#include "./land.hpp"
#include "./pipe.hpp"
#include "./bird.hpp"
#include "./collision.hpp"
#include "./flash.hpp"
#include "./hud.hpp"

namespace evansofts {

    class GameState: public State {
    public:
        enum class GameStates {
            Ready,
            Playing,
            GameOver
        };

        GameState(GameDataRef data);

        void Init();

        void HandleInput() override;
        void Update(float dt) override;
        void Draw(float dt) override;
    
    private:
        GameDataRef _data;
        sf::Sprite _background;
        std::unique_ptr<Pipe> pipe;
        std::unique_ptr<Land> land;
        std::unique_ptr<Bird> bird;
        std::unique_ptr<Flash> flash;
        std::unique_ptr<Hud> hud;
        
        Collision collision;
        GameStates _state;
        sf::Clock _clock;

        int _score;

        sf::SoundBuffer hitSb;
        sf::SoundBuffer wingSb;
        sf::SoundBuffer pointSb;

        sf::Sound hitSound;
        sf::Sound wingSound;
        sf::Sound pointSound;

    };

}


#endif