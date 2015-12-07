#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "entity.h"

#define PADDLE_SPEED 400 // in px per seconds

class Paddle : public IEntity
{
public:
    Paddle ();
    virtual ~Paddle () {};
    void draw(sf::RenderWindow &window) override;
    void update(float elapsed_time) override;

private:
    sf::Sprite m_sprite;
};
#endif
