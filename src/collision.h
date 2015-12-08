#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "shapes.h"

typedef enum Side {
    NORTH, EAST, SOUTH, WEST
} Side;

typedef struct Collision {
    float depth = 0.0f;
    glm::vec2 push_back;
    bool collides = false;
    Side side;
} Collision;

const Collision getCollisionBetweenCircleAndRect(const Circle& c,
        const Rectangle& r);

const Collision getCollisionOfRectWithinBounds(const Rectangle& rect,
        const Rectangle& frame);

#endif
