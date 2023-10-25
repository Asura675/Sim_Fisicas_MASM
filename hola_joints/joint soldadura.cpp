#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 30.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Articulacion de Soldadura");

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    b2BodyDef weldBlockDef;
    weldBlockDef.type = b2_staticBody;
    weldBlockDef.position.Set(400.0f / SCALE, 300.0f / SCALE);
    b2Body* weldBlockBody = world.CreateBody(&weldBlockDef);

    b2PolygonShape weldBlockShape;
    weldBlockShape.SetAsBox(100.0f / (2 * SCALE), 50.0f / (2 * SCALE));

    b2FixtureDef weldBlockFixtureDef;
    weldBlockFixtureDef.shape = &weldBlockShape;
    weldBlockBody->CreateFixture(&weldBlockFixtureDef);

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1.0f / 60.0f, velocityIterations, positionIterations);

        window.clear();

        sf::RectangleShape weldBlock(sf::Vector2f(100.0f, 50.0f));
        weldBlock.setFillColor(sf::Color::Green);
        weldBlock.setOrigin(50.0f, 25.0f);
        weldBlock.setPosition(weldBlockBody->GetPosition().x * SCALE, weldBlockBody->GetPosition().y * SCALE);
        weldBlock.setRotation(weldBlockBody->GetAngle() * 180 / b2_pi);
        window.draw(weldBlock);

        window.display();
    }

    return 0;
}