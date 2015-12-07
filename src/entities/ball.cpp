#include "ball.h"
#include <iostream>
#include "path.h"
#include "texture_manager.h"
#include "glm_helper.h"
#include "random.h"
#include <math.h>
#include "game.h"

#include "brick.h"

#define PI 3.14159265

Ball::Ball(int radius) {
    // Setup the balls texture and position
    sf::Texture* t = TextureManager::get(Path::resourcePath("ball.png"));
    m_sprite.setTexture(*t);
    auto bounds = m_sprite.getLocalBounds();
    sf::Vector2u windowSize = Game::window->getSize();
    m_sprite.setOrigin(bounds.width/2, bounds.height/2);
    m_sprite.setPosition(windowSize.x/2, windowSize.y - 100);

    // Launch the ball in a random direction
    int angularOffset = get_rand(10, 170);
    m_velocity.x = BALL_SPEED * cos(angularOffset * PI / 180);
    m_velocity.y = BALL_SPEED * -sin(angularOffset * PI / 180);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(this->m_sprite);
}

void Ball::update(float elapsed_time) {
    move(elapsed_time);

    auto bounds = m_sprite.getGlobalBounds();

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
        if (b->isAlive() && b->getGlobalBounds().intersects(m_sprite.getGlobalBounds())) {
            b->kill();
            sf::FloatRect brick_bounds = b->getGlobalBounds();
            sf::FloatRect ball_bounds = getGlobalBounds();
            float diffx = brick_bounds.left - ball_bounds.left;
            float diffy = brick_bounds.top - ball_bounds.top;
            std::cout << vec2ToString({diffx, diffy}) << std::endl;
            if (diffy > diffx) m_velocity.y = -m_velocity.y;
            else m_velocity.x = -m_velocity.x;
        }
    }
}

sf::FloatRect Ball::getGlobalBounds() {
    return m_sprite.getGlobalBounds();
}

void Ball::move(float elapsed_time) {
    glm::vec2 offset = m_velocity * (elapsed_time / 1000);
    m_sprite.move(offset.x, offset.y);
}
