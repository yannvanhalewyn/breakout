#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "entity.h"

#define PADDLE_SPEED 550 // in px per seconds

class Paddle : public IEntity
{
public:
    Paddle ();
    virtual ~Paddle () {};
    void draw(sf::RenderWindow &window) override;
    void update(float elapsed_time) override;
    sf::FloatRect getGlobalBounds() override;
private:
    sf::Sprite m_sprite;
};
#endif
