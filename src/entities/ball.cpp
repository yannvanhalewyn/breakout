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
#include "collision.h"

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

void Ball::update(float elapsed_time) {
    move(elapsed_time);

    auto bounds = m_circle.getGlobalBounds();

    // Bounce around borders of window
    sf::Vector2u window_size = Game::window->getSize();
    sf::FloatRect window_bounds = sf::FloatRect(0, 0, window_size.x, window_size.y);
    if (!isWithinWidth(bounds, window_bounds)) {
        m_velocity.x = - m_velocity.x;
        move(elapsed_time);
    }
    if (!isWithinHeight(bounds, window_bounds)) {
        m_velocity.y = - m_velocity.y;
        move(elapsed_time);
    }

    // Check for collision with paddle
    sf::FloatRect paddleBounds = EntityManager::getPaddle()->getGlobalBounds();
    if (paddleBounds.intersects(getGlobalBounds())) {
        if (m_velocity.y > 0) m_velocity.y = -m_velocity.y;
    }

    // Check for collision with a brick
    std::vector<IEntity*> bricks = EntityManager::getBricks();
    for (IEntity* brick : bricks) {
        Brick* b = static_cast<Brick*>(brick);
        // Broad collision check
        if (b->isAlive() && b->getGlobalBounds().intersects(m_circle.getGlobalBounds())) {
            // Deeper check
            Circle c({m_circle.getPosition().x, m_circle.getPosition().y},
                      m_circle.getRadius());
            sf::FloatRect brick_bounds = b->getGlobalBounds();
            Rectangle r(brick_bounds.left, brick_bounds.top,
                        brick_bounds.width, brick_bounds.height);
            Collision coll = getCollisionBetweenCircleAndRect(c, r);
            if (coll.collides) {
                glm::vec2 v = c.center - r.getCenter();
                b->kill();
                m_circle.move(coll.push_back.x, coll.push_back.y);
                std::cout << getSideFromAngle(coll.angle) << std::endl;
                switch (getSideFromAngle(coll.angle)) {
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
    }
}

sf::FloatRect Ball::getGlobalBounds() {
    return m_circle.getGlobalBounds();
}

void Ball::move(float elapsed_time) {
    glm::vec2 offset = m_velocity * (elapsed_time / 1000);
    m_circle.move(offset.x, offset.y);
}
