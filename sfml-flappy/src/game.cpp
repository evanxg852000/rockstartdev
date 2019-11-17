#include <cstdlib>
#include <ctime>

#include "./game.hpp"
#include "./splashstate.hpp"

namespace evansofts {
    Game::Game(int width, int height, std::string title){
        srand(time(NULL));
        _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
        _data->machine.AddState(StateRef(new SplashState(this->_data)));
        this->Run();
    }

    void Game::Run(){
        // Game loop (1) 
        // _data->window.setFramerateLimit(60); or _data->window.setVerticalSyncEnabled(true);
        // sf::Clock deltaClock;
        // sf::Time dt;
        // while(this->_data->window.isOpen()){
        //     dt = deltaClock.restart();
        //     this->_data->machine.ProcessStateChanges();
        //     this->_data->machine.GetActiveState()->HandleInput();
        //     this->_data->machine.GetActiveState()->Update(dt.asSeconds());
        //     this->_data->machine.GetActiveState()->Draw(dt.asSeconds()); 
        // }

        float newTime, frameTime, interpolation;

        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while(this->_data->window.isOpen()){
            this->_data->machine.ProcessStateChanges();
            newTime = this->_clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;
            if(frameTime > 0.25f)
                frameTime = 0.25f;

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= dt){
                this->_data->machine.GetActiveState()->HandleInput();
                this->_data->machine.GetActiveState()->Update(dt);

                accumulator -= dt;
            }

            interpolation = accumulator / dt;
            this->_data->machine.GetActiveState()->Draw(interpolation);
            
        }
        
    }
}