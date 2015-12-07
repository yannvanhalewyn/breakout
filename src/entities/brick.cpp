#include "brick.h"
#include "texture_manager.h"
#include "path.h"

Brick::Brick(int x, int y) : m_rect(BRICK_SIZE) {
    sf::Texture* t = TextureManager::get(Path::resourcePath("brick.jpg"));
    m_rect.setTexture(t);
    m_rect.setPosition(x, y);
}

void Brick::draw(sf::RenderWindow &window) {
    if (m_alive) window.draw(m_rect);
}

void Brick::update(float time_delta) {
}

sf::FloatRect Brick::getGlobalBounds() {
    return m_rect.getGlobalBounds();
}

