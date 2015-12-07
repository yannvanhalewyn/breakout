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
    Ball* ball = new Ball(15);
    m_entity_manager->addEntity(ball);
    Paddle* paddle = new Paddle();
    m_entity_manager->addEntity(paddle);

    // Add bricks
#define NUM_BRICKS_X 10
#define NUM_BRICKS_Y 3
#define OFFSET_X 100
#define OFFSET_Y 100

    for (int x = 0; x < NUM_BRICKS_X; ++x) {
        for (int y = 0; y < NUM_BRICKS_Y; ++y) {
            Brick* brick = new Brick(OFFSET_X + 100 * x, OFFSET_Y + 40 * y);
            m_entity_manager->addEntity(brick);
            m_entity_manager->recordBrick(brick);
        }
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
