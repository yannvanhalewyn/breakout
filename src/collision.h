#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "shapes.h"

typedef struct Collision {
    float depth;
    glm::vec2 push_back;
    bool collides;
    float angle;
} Collision;

const Collision getCollisionBetweenCircleAndRect(const Circle& c,
        const Rectangle& r);

typedef enum Side {
    NORTH, EAST, SOUTH, WEST
} Side;

Side getSideFromAngle(float angle);

#endif
