#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

class Collision {
public:
    static bool checkRectangleCollision(const SDL_Rect&  rectA,const SDL_Rect& rectB);

};


#endif