#include "game.h"

#include "ball.h"
#include "paddle.h"

Game::~Game() {
    delete window;
}

void Game::init() {
    // Setup window if needed
    if (!window) {
        window = new sf::RenderWindow({1200, 600}, "Breakout");
        window->setFramerateLimit(60);
    }

    // Setup entities
    Ball* b1 = new Ball(20);
    Ball* b2 = new Ball(50);
    Ball* b3 = new Ball(10);
    m_entity_manager.addEntity(b1);
    m_entity_manager.addEntity(b2);
    m_entity_manager.addEntity(b3);
    Paddle* p = new Paddle();
    m_entity_manager.addEntity(p);
}

void Game::run() {
    while(window->isOpen()) {
        sf::Event e;
        while(window->pollEvent(e)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window->close();
            if (e.type == sf::Event::Closed) window->close();
        }
        window->clear(sf::Color::Black);
        m_entity_manager.updateAll();
        m_entity_manager.drawAll(*window);
        window->display();
    }
}

sf::RenderWindow* Game::window;
