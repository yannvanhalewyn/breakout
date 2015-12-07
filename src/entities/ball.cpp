#include "ball.h"
#include <iostream>
#include "path.h"
#include "texture_manager.h"
#include "glm_helper.h"
#include "random.h"
#include <math.h>

#define PI 3.14159265

Ball::Ball(int radius) {
    // Setup the balls texture and position
    sf::Texture* t = TextureManager::get(Path::resourcePath("ball.png"));
    m_sprite.setTexture(*t);
    auto bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width/2, bounds.height/2);
    m_sprite.setPosition(600, 600);

    // Launch the ball in a random direction
    int angularOffset = get_rand(10, 170);
    m_velocity.x = BALL_SPEED * cos(angularOffset * PI / 180);
    m_velocity.y = BALL_SPEED * -sin(angularOffset * PI / 180);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(this->m_sprite);
}

const sf::FloatRect WINDOW_BOUNDS = sf::FloatRect(0, 0, 1200, 780);

void Ball::update(float elapsed_time) {
    glm::vec2 offset = m_velocity * (elapsed_time / 1000);
    m_sprite.move(offset.x, offset.y);
    auto bounds = m_sprite.getGlobalBounds();
    if (!isWithinWidth(bounds, WINDOW_BOUNDS)) {
        m_velocity.x = - m_velocity.x;
    }
    if (!isWithinHeight(bounds, WINDOW_BOUNDS)) {
        m_velocity.y = - m_velocity.y;
    }
}
