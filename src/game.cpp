#include "game.h"

#include "ball.h"
#include "paddle.h"
#include "brick.h"

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
    m_entity_manager = EntityManager::getInstance();
    Ball* ball = new Ball(20);
    m_entity_manager->addEntity(ball);
    Paddle* paddle = new Paddle();
    m_entity_manager->addEntity(paddle);

    // Add bricks
#define NUM_BRICKS 10
    for (int i = 0; i < NUM_BRICKS; ++i) {
        Brick* brick = new Brick(50 + 120 * i, 50);
        m_entity_manager->addEntity(brick);
    }

    m_entity_manager->recordPaddle(paddle);
    m_entity_manager->recordBall(ball);
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
    }
}

sf::RenderWindow* Game::window;
