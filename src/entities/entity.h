#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "SFML/Graphics.hpp"

class IEntity
{
public:
    virtual ~IEntity () {}
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(float time_delta) = 0;
};
#endif
