#include "SFML_2D-Animation.h"
#include <SFML/Graphics.hpp>
#include "Character.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "2D Animation");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Character soldier;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Time deltaTime = clock.restart();

        window.clear();

        soldier.update(deltaTime.asSeconds());
        soldier.draw(window);

        window.display();
    }
}
