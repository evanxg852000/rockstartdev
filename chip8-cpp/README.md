## SFML Game (conan)

# Add bincrafter repository
```bash
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

# How to build
```bash
mkdir build && cd build
conan install ..  -s build_type=Release --build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/app
```

# For SDL2
Add libraries
```
sdl2/2.0.12@bincrafters/stable
sdl2_ttf/2.0.15@bincrafters/stable
sdl2_mixer/2.0.4@bincrafters/stable
sdl2_image/2.0.5@bincrafters/stable
```


```cpp
#include <SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
```