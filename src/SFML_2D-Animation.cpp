#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "SFML_2D-Animation.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "2D Animation");
    window.setFramerateLimit(60);

    sf::Clock clock;

    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("map/map.png")) {
        std::cout << "Failed to load map texture!\n";
    }
    sf::Sprite mapSprite = sf::Sprite(mapTexture);
    mapSprite.setOrigin({ 240,160 });
    mapSprite.setScale({ 1.7f, 2.f });
    mapSprite.setPosition({ 400,300 });

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

        window.draw(mapSprite);

        orc.update(deltaTime.asSeconds());
        orc.draw(window);

        soldier.update(deltaTime.asSeconds());
        if (soldier.isColliding(orc.getCharBounds())) {
            soldier.takeDamage(orc.GetCharDamage(), deltaTime.asSeconds());
        }
        soldier.draw(window);

        //DEBUG COLLISION
        //auto drawBounds = [&](const sf::FloatRect& rect, sf::Color color) {
        //    sf::RectangleShape debugBox;
        //    debugBox.setPosition(rect.position);
        //    debugBox.setSize(rect.size);
        //    debugBox.setFillColor(sf::Color::Transparent);
        //    debugBox.setOutlineColor(color);
        //    debugBox.setOutlineThickness(1.f);
        //    window.draw(debugBox);
        //    };

        //drawBounds(soldier.getCharBounds(), sf::Color::Red);
        //drawBounds(orc.getCharBounds(), sf::Color::Green);

        window.display();
    }
}
