#include <iostream>

#include <glm/glm.hpp>
#include <catch2/catch.hpp>
#include <SFML/Graphics.hpp>


int main(int argc, char const *argv[]){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML");
    window.setFramerateLimit(30);

    sf::Event event;

    sf::Clock deltaClock;
    float delta = 1;

    while (window.isOpen()){

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        //...
        mySprite.Move(velocity * delta);

        delta = deltaClock.Restart().AsSeconds();
    }

    return 0;
}
