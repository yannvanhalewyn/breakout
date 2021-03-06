#include "entity_manager.h"
#include <iostream>

EntityManager* EntityManager::getInstance() {
    if (!instance) {
        instance = new EntityManager;
    }
    return instance;
}

EntityManager::~EntityManager() {
    for (IEntity* e : m_entities) {
        delete e;
    }
}

void EntityManager::addEntity(IEntity* entity) {
    m_entities.push_back(entity);
}

void EntityManager::deleteEntity(IEntity* entity) {
}

void EntityManager::updateAll() {
    float dt = m_clock.restart().asMilliseconds();
    for (IEntity* e : m_entities) {
        e->update(dt);
    }
}

void EntityManager::drawAll(sf::RenderWindow& window) {
    for (IEntity* e : m_entities) {
        e->draw(window);
    }
}

void EntityManager::clearAll() {
    for (IEntity* e : m_entities) {
        delete e;
    }
    m_entities.clear();
    m_bricks.clear();
    m_paddle = nullptr;
    m_ball = nullptr;
}

EntityManager* EntityManager::instance;
IEntity* EntityManager::m_paddle;
IEntity* EntityManager::m_ball;
std::vector<IEntity*> EntityManager::m_bricks;
