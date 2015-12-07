#include "brick.h"
#include "texture_manager.h"
#include "path.h"

Brick::Brick(int x, int y) {
    sf::Texture* t = TextureManager::get(Path::resourcePath("brick.jpg"));
    m_sprite.setPosition(x, y);
    m_sprite.setTexture(*t);
    m_sprite.setScale(0.8, 0.8);
}

void Brick::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

void Brick::update(float time_delta) {
}

sf::FloatRect Brick::getGlobalBounds() {
    return m_sprite.getGlobalBounds();
}

