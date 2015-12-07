#include "ball.h"
#include <iostream>
#include "path.h"

Ball::Ball(int radius) {
    m_ball_texture.loadFromFile(Path::resourcePath("ball.png"));
    m_sprite.setTexture(m_ball_texture);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(this->m_sprite);
}
