#ifndef __BRICK_H__
#define __BRICK_H__

#include "entity.h"

class Brick : public IEntity
{
public:
    Brick (int x, int y);
    virtual ~Brick () {}

    void draw(sf::RenderWindow &window) override;
    void update(float time_delta) override;
    sf::FloatRect getGlobalBounds() override;
    void kill() { m_alive = false; }
    bool isAlive() { return m_alive; }

private:
    sf::Sprite m_sprite;
    bool m_alive = true;
    /* data */
};
#endif
