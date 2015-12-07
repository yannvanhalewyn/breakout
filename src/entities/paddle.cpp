#include "paddle.h"
#include "texture_manager.h"
#include "path.h"
#include "game.h"

Paddle::Paddle() {
    sf::Texture* t = TextureManager::get(Path::resourcePath("paddle.png"));
    m_sprite.setTexture(*t);
    auto bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width/2, bounds.height/2);
    sf::Vector2u windowSize = Game::window->getSize();
    m_sprite.setPosition(windowSize.x / 2, windowSize.y - 50);
}

void Paddle::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

void Paddle::update(float elapsed_time) {
    float offset = PADDLE_SPEED * elapsed_time / 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_sprite.move(-offset, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_sprite.move(offset, 0);
    }
}
