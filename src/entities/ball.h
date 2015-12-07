#ifndef __BAL_H__
#define __BAL_H__

#include "entity.h"
#include <glm/glm.hpp>

#define BALL_SPEED 400 // px per second

class Ball : public IEntity
{
public:
    Ball (int radius);
    virtual ~Ball () {}
    void draw(sf::RenderWindow &window) override;
    void update(float elapsed_time) override;

private:
    sf::Sprite m_sprite;
    glm::vec2 m_velocity; // in pixel/s

    void move(float elapsed_time);
};

#endif
