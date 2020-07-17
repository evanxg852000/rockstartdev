#include "game.hpp"


int main(int argc, char* argv[]) {
    evansofts::GameOptions opts{
        .title = "SFML Game",
        .width = 800u, 
        .height = 600u,
        .bitPerPixel = 32u,
        .vSync = true,
        .fullScreen = false,
        .maxFps = 33u,
        .showFps = true
    };
    return AppGame{opts}.run();
}