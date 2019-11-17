#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include <SFML/Graphics.hpp>

#include "./state.hpp"
#include "./game.hpp"

namespace evansofts {

    class GameOverState: public State {
    public:
        GameOverState(GameDataRef data, int score);

        void Init();

        void HandleInput() override;
        void Update(float dt) override;
        void Draw(float dt) override;
    
    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Sprite _gameOverTitle;
        sf::Sprite _gameOverContainer;
        sf::Sprite _retryButton;
        sf::Sprite _medal;

        sf::Text _scoreText;
        sf::Text _highScoreText;

        int _score;
        int _highScore; 
    };

}


#endif