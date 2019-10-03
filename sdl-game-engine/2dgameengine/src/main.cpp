#include <iostream>
#include <memory>

#include "./constants.h"
#include "./game.h"

int main(int argc, char const *argv[]){
    auto game = std::make_unique<Game>();

    game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while(game->isRunning()){
        game->processInput();
        game->update();
        game->render();
    }
    
    //game->destroy();
    return EXIT_SUCCESS;
}
