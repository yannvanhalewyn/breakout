#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

constexpr int windowWidth(800);
constexpr int windowHeight(600);

int main(int argc, char *argv[])
{
    sf::RenderWindow window{{windowWidth, windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
            if (e.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }

    std::cout << "Hello World!" << std::endl;
    return 0;
}
