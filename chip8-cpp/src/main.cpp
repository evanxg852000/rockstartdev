#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "chip8.hpp"

void updateKeyPad(Chip8 &chip8) {
    chip8.key[0x1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1);
    chip8.key[0x2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2);
    chip8.key[0x3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3);
    chip8.key[0xC] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4);
    
    chip8.key[0x4] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    chip8.key[0x5] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    chip8.key[0x6] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    chip8.key[0xD] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
    
    chip8.key[0x7] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    chip8.key[0x8] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    chip8.key[0x9] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    chip8.key[0xE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F);
    
    chip8.key[0xA] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    chip8.key[0x0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X);
    chip8.key[0xB] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C);
    chip8.key[0xF] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V);
}

void renderGraphics(const Chip8 &chip8, sf::RenderWindow &window) {
    // Lets define a pixel size (constant)
    sf::RectangleShape pixel(sf::Vector2f(13,13));
    for(int y=0; y < 32; ++y){
        for(int x=0; x < 64; ++x){
            unsigned char pixelState = chip8.gfx[x+(64*y)];
            if(pixelState > 0){
                pixel.setPosition((float)(x*13), (float)(y*13));
                window.draw(pixel);
            }
        }
    }
}


int main(int argc, char* argv[]) {
    // get rom file 
    if(argc < 2) {
        std::cerr << "Usage `chip8 rom` !" << std::endl;
        return EXIT_FAILURE;
    }

    auto romfile = argv[1];

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(832, 416), "CHIP-8");
    window.setFramerateLimit(60);

    Chip8 chip8{};
    chip8.load(romfile);

    // Start the game loop
    static float refreshSpeed = 1.f/180.f;
    sf::Clock clock;
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        if(clock.getElapsedTime().asSeconds() >= refreshSpeed){
            updateKeyPad(chip8);
            chip8.emulateCycle();
            if(chip8.drawFlag) {
                window.clear();
                renderGraphics(chip8, window);
                window.display();
                chip8.drawFlag = false;
            }
            clock.restart();
        }
         
    }

    return EXIT_SUCCESS;
}