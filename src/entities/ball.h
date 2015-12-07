#ifndef __BAL_H__
#define __BAL_H__

#include "game_object.h"
#include <glm/glm.hpp>

class Ball : public IGameObject
{
public:
    Ball (int radius);
    virtual ~Ball () {}
    void draw(sf::RenderWindow &window);
    void update(float elapsed_time);

private:
    sf::Sprite m_sprite;
    glm::vec2 m_velocity; // in pixel/s
};

#endif
