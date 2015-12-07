#include "ball.h"
#include <iostream>
#include "path.h"
#include "texture_manager.h"

Ball::Ball(int radius) {
    sf::Texture* t = TextureManager::get(Path::resourcePath("ball.png"));
    m_sprite.setTexture(*t);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(this->m_sprite);
}
