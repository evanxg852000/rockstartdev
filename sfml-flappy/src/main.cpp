#include <iostream>

#include <glm/glm.hpp>
#include <catch2/catch.hpp>

#include "./game.hpp"
#include "./definitions.hpp"


int main(int argc, char const *argv[]){
    evansofts::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    return EXIT_SUCCESS;
}
