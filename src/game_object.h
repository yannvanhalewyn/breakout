#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "SFML/Graphics.hpp"

class IGameObject
{
public:
    virtual ~IGameObject () {}
    virtual void draw(sf::RenderWindow &window) = 0;
    // virtual void update(size_t delta_time);
};
#endif
