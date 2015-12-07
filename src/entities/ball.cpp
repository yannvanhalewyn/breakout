#include "ball.h"
#include <iostream>
#include "path.h"
#include "texture_manager.h"
#include "glm_helper.h"
#include "random.h"
#include <math.h>
#include "game.h"

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
}

void Ball::move(float elapsed_time) {
    glm::vec2 offset = m_velocity * (elapsed_time / 1000);
    m_sprite.move(offset.x, offset.y);
}
