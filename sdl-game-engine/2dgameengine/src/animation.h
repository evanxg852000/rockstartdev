#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>

class Animation {
public:
    Animation();
    Animation(int index, int numFrames, int animationSpeed);
    int index;
    int numFrames;
    int animationSpeed;

};

#endif