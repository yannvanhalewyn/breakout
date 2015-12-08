#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "entity_manager.h"

class Game
{
public:
    Game () {}
    virtual ~Game ();
    void init();
    void run();
    static sf::RenderWindow* window;

private:
    EntityManager* m_entity_manager;
    int m_current_level = 1;
};

#endif
