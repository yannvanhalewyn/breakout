#include "shapes.h"

Rectangle rectFromSFMLBounds(const sf::FloatRect& rect) {
    return Rectangle(rect.left, rect.top, rect.width, rect.height);
}

Rectangle rectFromSFMLSize(const sf::Vector2u& size) {
    return Rectangle(0, 0, size.x, size.y);
}

Circle circleFromSFMLCircle(const sf::CircleShape& c) {
    return Circle({c.getPosition().x, c.getPosition().y}, c.getRadius());
}
