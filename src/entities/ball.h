#ifndef __BAL_H__
#define __BAL_H__

#include "game_object.h"

class Ball : public IGameObject
{
public:
    Ball (int radius);
    virtual ~Ball () {}
    void draw(sf::RenderWindow &window);

private:
    sf::Sprite m_sprite;
};

#endif
