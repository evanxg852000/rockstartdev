#include <iostream>

#include <glm/glm.hpp>
#include <catch2/catch.hpp>
#include <SFML/Graphics.hpp>


int main(int argc, char const *argv[]){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML");

    sf::Event event;

    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
    }

    return 0;
}
