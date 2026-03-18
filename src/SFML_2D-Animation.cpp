#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "SFML_2D-Animation.h"
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
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

    //Box2D configuration
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 0.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    b2BodyDef wallDef = b2DefaultBodyDef();
    wallDef.type = b2_staticBody;
    b2ShapeDef shapeDef = b2DefaultShapeDef();

    float SCALE = 30.0f;
    float hw = (SCREEN_WIDTH / 2.f) / SCALE; //half-width
    float hh = (SCREEN_HEIGHT / 2.f) / SCALE; //half-height
    float thickness = 1.0f;
    // TOP
    wallDef.position = { hw, -thickness };
    b2BodyId topWall = b2CreateBody(worldId, &wallDef);
    b2Polygon topShape = b2MakeBox(hw, thickness);
    b2CreatePolygonShape(topWall, &shapeDef, &topShape);
    // BOTTOM
    wallDef.position = { hw, (SCREEN_HEIGHT / SCALE) + thickness };
    b2BodyId bottomWall = b2CreateBody(worldId, &wallDef);
    b2Polygon bottomShape = b2MakeBox(hw, thickness);
    b2CreatePolygonShape(bottomWall, &shapeDef, &bottomShape);
    // LEFT
    wallDef.position = { -thickness, hh };
    b2BodyId leftWall = b2CreateBody(worldId, &wallDef);
    b2Polygon leftShape = b2MakeBox(thickness, hh);
    b2CreatePolygonShape(leftWall, &shapeDef, &leftShape);
    // RIGHT
    wallDef.position = { (SCREEN_WIDTH / SCALE) + thickness, hh };
    b2BodyId rightWall = b2CreateBody(worldId, &wallDef);
    b2Polygon rightShape = b2MakeBox(thickness, hh);
    b2CreatePolygonShape(rightWall, &shapeDef, &rightShape);

    Player soldier = Player(worldId);
    Enemy orc = Enemy(worldId);
    
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

        b2World_Step(worldId, deltaTime.asSeconds(), 4);

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
