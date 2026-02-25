#include "SFML_2D-Animation.h"
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Enemy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "2D Animation");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Player soldier;
    Enemy orc;

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
        orc.update(deltaTime.asSeconds());
        orc.draw(window);

        window.display();
    }
}
