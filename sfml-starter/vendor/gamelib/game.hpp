#pragma once

#include <cstddef>
#include <random>
#include <string>
#include <algorithm> 
#include <chrono> 
#include <cmath> 
#include <cstdio>
#include <stdexcept>
#include <system_error>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <fmt/format.h>

namespace evansofts {

struct GameOptions final {
    const char* title = "Game";
    unsigned width = 800u;
    unsigned height = 600u;
    unsigned bitPerPixel = 32u;
    bool vSync = false;
    bool fullScreen = false;
    unsigned maxFps = 0u;
    bool showFps = false;
};

class Game {
public:
	Game(GameOptions opts) noexcept : _options{opts} {
        try {
            this->initWindow();
            this->initFps();
        } catch (const std::exception& e) {
            fmt::print(stderr, "{}\n", e.what());
            quit(1);
        } catch (...) {
            fmt::print(stderr, "Failed to initialise game!\n");
            this->quit(1);
        }
    }

    virtual ~Game() noexcept = default;

	int virtual run() {
        using namespace std::chrono_literals;
        using float_seconds = std::chrono::duration<float>;
        auto latest_frame_time = std::chrono::steady_clock::now();
        auto latest_fps_count_time = latest_frame_time;
        auto frame_counter = 0u;
        while (_isRunning) {
            const auto current_time = std::chrono::steady_clock::now();
            const auto delta_time = current_time - latest_frame_time;
            const auto delta_time_seconds = std::chrono::duration_cast<float_seconds>(delta_time);
            const auto delta_time_seconds_count = delta_time_seconds.count();
            if (delta_time_seconds_count >= _minimumDeltaTime) {
                latest_frame_time = current_time;
                ++frame_counter;
                if (current_time - latest_fps_count_time >= 1s) {
                    latest_fps_count_time = current_time;
                    _fpsText.setString(fmt::format("FPS: {} Hz", frame_counter));
                    frame_counter = 0u;
                }
                handleEvents();
                update(delta_time_seconds_count);
                draw();
            }
        }
        return _exitCode;
    }

	void quit(int exit_code = 0) {
        _exitCode = exit_code;
	    _isRunning = false;
    }

protected:

    void initWindow() {
        const auto video_mode = sf::VideoMode{_options.width, _options.height, _options.bitPerPixel};
        auto window_style = sf::Style::Titlebar | sf::Style::Close;
        if (_options.fullScreen) {
            if (!video_mode.isValid()) {
                throw std::runtime_error{fmt::format("Invalid fullscreen video mode \"{}x{} px @ {} bpp\"!", video_mode.width, video_mode.height, video_mode.bitsPerPixel)};
            }
            window_style |= sf::Style::Fullscreen;
        }
        _window.create(video_mode, _options.title, window_style);
        if (!_window.isOpen()) {
            throw std::runtime_error{"Failed to open main window!"};
        }
        _window.setVerticalSyncEnabled(_options.vSync);
        _screenBounds = sf::FloatRect{0.0f, 0.0f, static_cast<float>(_options.width), static_cast<float>(_options.height)};
    }

	void initFps() {
        const char* font_file = "data/arial.ttf";
        if (!_fpsFont.loadFromFile(font_file)) {
            throw std::runtime_error{fmt::format("Failed to load font \"{}\"!", font_file)};
        }
        _fpsText.setFont(_fpsFont);
        _fpsText.setCharacterSize(21u);
        _fpsText.setFillColor(sf::Color::White);
        _fpsText.setString("FPS:");
        _fpsText.setPosition(0.0f, 0.0f);

        if (_options.maxFps == 0u) {
            _minimumDeltaTime = 0.0f;
        } else {
            _minimumDeltaTime = 1.0f / _options.maxFps;
        }
    }

    void handleEvents() {
        for (auto e = sf::Event{}; _window.pollEvent(e);) {
            if(this->process(e)){
                continue;
            } else if (e.type == sf::Event::Closed) {
                quit();
            } else if (e.type == sf::Event::KeyPressed && e.key.code ==  sf::Keyboard::Escape) {
                quit();
            }
        }
    }
    
    virtual void init() = 0;

	virtual bool process(sf::Event evt) = 0;
    
	virtual void update(float delta_time) = 0;
	
    virtual void draw() {
        if(_options.showFps)
            _window.draw(_fpsText);
	    _window.display();
    };


	sf::RenderWindow _window;
    GameOptions _options;
    sf::Font _fpsFont;
    sf::Text _fpsText;
    float _minimumDeltaTime = 0.0f;
	int _exitCode = 0;
	bool _isRunning = true;
    sf::FloatRect _screenBounds;
};

} // namespace evansofts
