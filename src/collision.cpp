#include "collision.h"
#include <iostream>
#include <glm/gtx/euler_angles.hpp>

inline Side getCirclesSideFromRect(const Circle& c, const Rectangle& r) {
    if (c.center.y < r.top) return NORTH;
    if (c.center.y > r.top + r.height) return SOUTH;
    if (c.center.x < r.left) return WEST;
    return EAST;
}

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

    collision.side = getCirclesSideFromRect(c, r);
    return collision;
}
