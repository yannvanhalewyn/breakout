#include "game.h"

#include "level_loader.h"
#include "ball.h"

Game::~Game() {
    delete window;
}

void Game::init() {
    // Setup window if needed
    if (!window) {
        window = new sf::RenderWindow({1200, 600}, "Breakout");
        window->setFramerateLimit(60);
    }

    loadLevel(1);
    m_entity_manager = EntityManager::getInstance();
}

void Game::run() {
    while(window->isOpen()) {
        sf::Event e;
        while(window->pollEvent(e)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window->close();
            if (e.type == sf::Event::Closed) window->close();
        }
        window->clear(sf::Color::Black);
        m_entity_manager->updateAll();
        m_entity_manager->drawAll(*window);
        window->display();

        // Check for game over
        if (static_cast<Ball*>(EntityManager::getBall())->wentOutOfBounds) {
            window->close();
        }
    }
}

sf::RenderWindow* Game::window;
