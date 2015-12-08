#ifndef __BAL_H__
#define __BAL_H__

#include "entity.h"
#include <glm/glm.hpp>
#include "collision.h"

class Ball : public IEntity
{
public:
    Ball (float speed = 500, int radius = 15);
    virtual ~Ball () {}
    void draw(sf::RenderWindow &window) override;
    void update(float elapsed_time) override;
    sf::FloatRect getGlobalBounds() override;
    bool wentOutOfBounds = false; // For the game to know when game is over

private:
    sf::CircleShape m_circle;
    glm::vec2 m_velocity; // in pixel/s

    void move(float elapsed_time);
    Collision getCollisionWithEntity(IEntity* e);
    void handleCollision(const Collision& coll);
    void collideWithWindowFrame();
};

#endif
