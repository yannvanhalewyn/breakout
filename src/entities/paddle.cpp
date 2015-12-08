#include "paddle.h"
#include "texture_manager.h"
#include "path.h"
#include "game.h"
#include "collision.h"
#include "iostream"

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

    // Check for window bounds
    sf::Vector2u w_size = Game::window->getSize();
    Rectangle w_rect(0, 0, w_size.x, w_size.y);
    sf::FloatRect p_bounds = getGlobalBounds();
    Rectangle p_rect(p_bounds.left, p_bounds.top,
            p_bounds.width, p_bounds.height);
    Collision coll = getCollisionOfRectWithinBounds(p_rect, w_rect);
    std::cout << coll.collides << std::endl;
    if (coll.collides) {
        m_sprite.move(coll.push_back.x, coll.push_back.y);
    }
}

sf::FloatRect Paddle::getGlobalBounds() {
    return m_sprite.getGlobalBounds();
}
