#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "SDL.h"

#include "Vector2.h"

class Transform
{
public:
    Transform();

    Vector2 position;
    Vector2 scale;
};

#endif
