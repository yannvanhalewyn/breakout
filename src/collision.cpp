#include "collision.h"
#include <iostream>
#include <glm/gtx/euler_angles.hpp>

const Collision getCollisionBetweenCircleAndRect(const Circle& c, const Rectangle& r) {

    // The return object
    Collision collision;

    glm::vec2 nearest_point_on_rect(
            glm::clamp(c.center.x, r.left, r.left + r.width),
            glm::clamp(c.center.y, r.top, r.top + r.height));

    float distance = glm::distance(nearest_point_on_rect, c.center);
    collision.collides = distance < c.radius;
    collision.depth = c.radius - distance;

    glm::vec2 v = c.center - r.getCenter();
    collision.push_back = glm::normalize(v) * collision.depth;
    collision.angle = glm::degrees(glm::atan(v.x, v.y));

    return collision;
}

#define between(V, X, Y) V > X && V <= Y
Side getSideFromAngle(float angle) {
    if (between(angle, -135, -45)) return WEST;
    if (between(angle, -45, 45)) return SOUTH;
    if (between(angle, 45, 135)) return EAST;
    return NORTH;
}
