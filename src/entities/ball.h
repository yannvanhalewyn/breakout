#ifndef __BAL_H__
#define __BAL_H__

#include "entity.h"
#include <glm/glm.hpp>

class Ball : public IEntity
{
public:
    Ball (int radius, glm::vec2 velocity = {20, -20});
    virtual ~Ball () {}
    void draw(sf::RenderWindow &window);
    void update(float elapsed_time);

private:
    sf::Sprite m_sprite;
    glm::vec2 m_velocity; // in pixel/s
};

#endif
