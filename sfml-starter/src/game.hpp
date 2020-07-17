#pragma once

#include <iostream>

#include <fmt/format.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <gamelib/game.hpp>

class AppGame : public evansofts::Game {
public:
    AppGame(evansofts::GameOptions opts) noexcept : Game{opts} {
        try {
            this->init();
        } catch (const std::exception& e) {
            fmt::print(stderr, "{}\n", e.what());
            quit(1);
        } catch (...) {
            fmt::print(stderr, "Failed to initialise app!\n");
            this->quit(1);
        }
    }

    virtual ~AppGame() noexcept = default;

protected:

    virtual void init() override {
        // Load a sprite to display
        if (!texture.loadFromFile("./data/bird_image.png"))
             std::runtime_error{"Failed to load image!"};
        sprite.setTexture(texture);

        // Create a graphical text to display
        if (!font.loadFromFile("./data/arial.ttf"))
             std::runtime_error{"Failed to load font!"};
        text.setFont(font);
        text.setCharacterSize(50);
        text.setString("Hello SFML");

        // Load a music to play
        if (!music.openFromFile("./data/bird_music.ogg"))
            std::runtime_error{"Failed to load music!"};
        music.play();
    }

	virtual bool process(sf::Event evt) override {
        //std::cout << fmt::format("processing event\n");
        return false;
    };
    
	virtual void update(float delta_time) override {
         //std::cout << fmt::format("updating with delta {}\n", delta_time);
    };
	
    virtual void draw() override {
        _window.clear();
        _window.draw(sprite);
        _window.draw(text);
        Game::draw();
    };

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Music music;
    sf::Text text;
};
