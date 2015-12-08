#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <glm/glm.hpp>
// For float rects and circle shapes factories
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>

typedef struct Circle {
    glm::vec2 center = {0, 0};
    float radius = 0;
    Circle(const glm::vec2& center = {0, 0}, float radius = 0) :
        center(center), radius(radius) {}
} Circle;

typedef struct Rectangle {
    float left = 0;
    float top = 0;
    float width = 0;
    float height = 0;
    Rectangle(float l = 0, float t = 0, float w = 0, float h = 0) :
        left(l), top(t), width(w), height(h) {}
    glm::vec2 getCenter() const {
        return glm::vec2(left + width/2, top + height/2);
    }
} Rectangle;

Rectangle rectFromSFMLBounds(const sf::FloatRect& rect);
Rectangle rectFromSFMLSize(const sf::Vector2u& size);
Circle circleFromSFMLCircle(const sf::CircleShape& c);

#endif
