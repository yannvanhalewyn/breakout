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

private:
    EntityManager() {}
    static EntityManager* instance;

    std::vector<IEntity*> m_entities;
    sf::Clock m_clock;
};
#endif
