#include "entity_manager.h"
#include <iostream>

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
    for (IEntity* e : m_entities) {
        e->update(100);
    }
}

void EntityManager::drawAll(sf::RenderWindow& window) {
    for (IEntity* e : m_entities) {
        e->draw(window);
    }
}

