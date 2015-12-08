#include "ball.h"
#include <iostream>
#include "path.h"
#include "texture_manager.h"
#include "glm_helper.h"
#include "random.h"
#include <math.h>
#include "game.h"

#include "brick.h"
#include "shapes.h"

#define PI 3.14159265

Ball::Ball(int radius) : m_circle(radius) {
    // Setup the balls texture and position
    auto bounds = m_circle.getLocalBounds();
    sf::Vector2u windowSize = Game::window->getSize();
    m_circle.setOrigin(bounds.width/2, bounds.height/2);
    m_circle.setPosition(windowSize.x/2, windowSize.y - 100);
    m_circle.setFillColor(sf::Color::Blue);

    // Launch the ball in a random direction
    int angularOffset = get_rand(10, 170);
    m_velocity.x = BALL_SPEED * cos(angularOffset * PI / 180);
    m_velocity.y = BALL_SPEED * -sin(angularOffset * PI / 180);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(this->m_circle);
}

inline const Rectangle rectFromEntity(IEntity* e) {
    sf::FloatRect bounds = e->getGlobalBounds();
    return Rectangle(bounds.left, bounds.top, bounds.width, bounds.height);
}

inline const Circle circleFromSFMLCircle(const sf::CircleShape& c) {
    return Circle({c.getPosition().x, c.getPosition().y}, c.getRadius());
}

Collision Ball::getCollisionWithEntity(IEntity* e) {
    Circle c = circleFromSFMLCircle(m_circle);
    Rectangle r = rectFromEntity(e);
    return getCollisionBetweenCircleAndRect(c, r);
}

void Ball::handleCollision(const Collision& coll) {
    // Only handle if it is a collision
    if (coll.collides) {
        // Move back out of the colliding body
        m_circle.move(coll.push_back.x, coll.push_back.y);
        // Bounce off the colliding body
        switch (coll.side) {
            case NORTH:
            case SOUTH:
                m_velocity.y = -m_velocity.y;
                break;
            case EAST:
            case WEST:
                m_velocity.x = -m_velocity.x;
                break;
        }
    }
}

void Ball::collideWithWindowFrame() {
    sf::Vector2u window_size = Game::window->getSize();
    sf::FloatRect bounds = getGlobalBounds();
    sf::FloatRect window_bounds = sf::FloatRect(0, 0, window_size.x,
            window_size.y);

    // Bounce off sides
    if (!isWithinWidth(bounds, window_bounds))
        m_velocity.x = - m_velocity.x;
    if (bounds.top <= 0)
        m_velocity.y = -m_velocity.y;

    // Adjust position to surely be within window
    sf::Vector2f pos = m_circle.getPosition();
    m_circle.setPosition(glm::clamp(pos.x, 0.0f, (float)window_size.x),
            pos.y < m_circle.getRadius() ? m_circle.getRadius() : pos.y);
}

void Ball::update(float elapsed_time) {
    move(elapsed_time);
    collideWithWindowFrame();

    // Check for general collision with paddle
    sf::FloatRect paddleBounds = EntityManager::getPaddle()->getGlobalBounds();
    if (paddleBounds.intersects(getGlobalBounds())) {
        // If general collision, handle fine calculations
        Collision col = getCollisionWithEntity(EntityManager::getPaddle());
        handleCollision(col);
    }

    // Check for collision with a brick
    std::vector<IEntity*> bricks = EntityManager::getBricks();
    for (IEntity* brick : bricks) {
        Brick* b = static_cast<Brick*>(brick);
        // Broad collision check
        if (b->isAlive() && b->getGlobalBounds()
                .intersects(m_circle.getGlobalBounds())) {
            // Deeper check
            Collision coll = getCollisionWithEntity(brick);
            handleCollision(coll);
            if (coll.collides) b->kill();
        }
    }
}

sf::FloatRect Ball::getGlobalBounds() {
    return m_circle.getGlobalBounds();
}

void Ball::move(float elapsed_time) {
    glm::vec2 offset = m_velocity * (elapsed_time / 1000);
    m_circle.move(offset.x, offset.y);
}
