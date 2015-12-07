#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity_manager.h"
#include "ball.h"

constexpr int windowWidth(800);
constexpr int windowHeight(600);

int main(int argc, char *argv[])
{
    sf::RenderWindow window{{windowWidth, windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);

    Ball* b1 = new Ball(20, {10, -50});
    Ball* b2 = new Ball(50, {40, -60});
    Ball* b3 = new Ball(10, {120, 130});
    EntityManager e_manager;
    e_manager.addEntity(b1);
    e_manager.addEntity(b2);
    e_manager.addEntity(b3);

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
            if (e.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::Black);
        e_manager.updateAll();
        e_manager.drawAll(window);
        window.display();
    }

    std::cout << "Hello World!" << std::endl;
    return 0;
}
