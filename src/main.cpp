#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "ball.h"

constexpr int windowWidth(800);
constexpr int windowHeight(600);

int main(int argc, char *argv[])
{
    sf::RenderWindow window{{windowWidth, windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);

    Ball ball(20);

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
            if (e.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::Black);
        ball.draw(window);
        ball.update(100);
        window.display();
    }

    std::cout << "Hello World!" << std::endl;
    return 0;
}
