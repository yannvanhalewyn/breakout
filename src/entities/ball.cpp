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

Collision Ball::getCollisionWithEntity(IEntity* e) {
    Circle c = circleFromSFMLCircle(m_circle);
    Rectangle r = rectFromSFMLBounds(e->getGlobalBounds());
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
    Collision coll = getCollisionOfRectWithinBounds(rectFromSFMLBounds(
                getGlobalBounds()),
                rectFromSFMLSize(Game::window->getSize()));

    if (coll.collides) {
        switch (coll.side) {
            case EAST:
            case WEST:
                m_circle.move(coll.push_back.x, coll.push_back.y);
                m_velocity.x = -m_velocity.x;
                break;
            case NORTH:
                m_circle.move(coll.push_back.x, coll.push_back.y);
                m_velocity.y = -m_velocity.y;
                break;
            case SOUTH:
                this->wentOutOfBounds = true;
                break;
        }
    }
    return;
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
