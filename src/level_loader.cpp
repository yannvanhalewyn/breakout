#include "level_loader.h"
#include "level.h"
#include "brick.h"
#include "paddle.h"
#include "ball.h"
#include "entity_manager.h"

#include <iostream>

#define BRICKS_X_OFFSET 50
#define BRICK_HEIGHT 40
#define BRICK_WIDTH 100

bool loadLevel(int n) {
    Level level = getLevel(n);

    EntityManager* entity_manager = EntityManager::getInstance();
    entity_manager->clearAll();

    // Add Ball and paddle
    Ball* ball = new Ball(level.ballInitialSpeed);
    Paddle* paddle = new Paddle();
    entity_manager->addEntity(ball);
    entity_manager->addEntity(paddle);
    entity_manager->recordPaddle(paddle);
    entity_manager->recordBall(ball);

    for (glm::vec2 b : level.brickPositions) {
        Brick* brick = new Brick(BRICKS_X_OFFSET + b.x * BRICK_WIDTH,
                                 b.y * BRICK_HEIGHT);
        entity_manager->addEntity(brick);
        entity_manager->recordBrick(brick);
    }

    return true;
}
