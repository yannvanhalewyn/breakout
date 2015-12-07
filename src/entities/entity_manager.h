#ifndef __GAME_OBJECT_MANAGER__
#define __GAME_OBJECT_MANAGER__

#include "entity.h"

class EntityManager
{
public:
    virtual ~EntityManager();
    void addEntity(IEntity* entity);
    void deleteEntity(IEntity* entity);
    void updateAll();
    void drawAll(sf::RenderWindow& window);

    static EntityManager* getInstance();

    void recordPaddle(IEntity* paddle) { m_paddle = paddle; }
    void recordBall(IEntity* ball) { m_ball = ball; }
    static IEntity* getBall() { return m_ball; }
    static IEntity* getPaddle() { return m_paddle; }

private:
    EntityManager() {}
    static EntityManager* instance;

    std::vector<IEntity*> m_entities;
    sf::Clock m_clock;

    static IEntity* m_paddle;
    static IEntity* m_ball;
};
#endif
