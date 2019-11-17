#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "./statemachine.hpp"
#include "./assetmanager.hpp"
#include "./inputmanager.hpp"


namespace evansofts {

    struct GameData {
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
    };

    using GameDataRef = std::shared_ptr<GameData>;


    class Game {
    public:
        Game(int width, int height, std::string title);
    
    private:
        const float dt = 1.0f / 60.0f;
        sf::Clock _clock;
        GameDataRef _data = std::make_shared<GameData>();

        void Run();

    };

}

#endif