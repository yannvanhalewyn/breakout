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

const Collision getCollisionOfRectWithinBounds(const Rectangle& rect,
        const Rectangle& frame) {
    Collision coll;

    // Out of left side
    if (rect.left < frame.left) {
        // Will not collide
        coll.collides = true;
        coll.depth = frame.left - rect.left;
        coll.push_back = glm::vec2(coll.depth, 0.0f);
        return coll;
    }

    // Out of right side
    if (rect.left + rect.width > frame.left + frame.width) {
        coll.collides = true;
        coll.depth = rect.left + rect.width - (frame.left + frame.width);
        coll.push_back = glm::vec2(-coll.depth, 0.0f);
        return coll;
    }

    // Out of top
    if (rect.top < frame.top) {
        coll.collides = true;
        coll.depth = frame.top - rect.top;
        coll.push_back = glm::vec2(0.0f, coll.depth);
        return coll;
    }

    // Out of bottom
    if (rect.top + rect.height > frame.top + frame.height) {
        coll.collides = true;
        coll.depth = rect.top + rect.height - (frame.top + frame.height);
        coll.push_back = glm::vec2(0.0f, -coll.depth);
        return coll;
    }

    // Default = collision
    return coll;
}
