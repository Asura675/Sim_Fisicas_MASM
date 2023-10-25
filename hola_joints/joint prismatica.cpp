#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Cube {
public:
    Cube(b2World& world, float x, float y, bool isStatic = false) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);

        if (isStatic) {
            bodydef.type = b2_staticBody;
        } else {
            bodydef.type = b2_dynamicBody;
        }

        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(10.f, 10.f));
        box.setFillColor(sf::Color::Green);
        box.setOrigin(5.f, 5.f);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow& win) const {
        win.draw(box);
    }

    void resetPosition() {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    b2Body* getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body* body;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Articulacion Prismatica");

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    Cube anchor(world, 400, 300, true);
    Cube movingCube(world, 500, 300);

    // Crear el joint prismático para conectar los cubos
    b2PrismaticJointDef prismaticJointDef;
    prismaticJointDef.Initialize(anchor.getBody(), movingCube.getBody(), movingCube.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
    prismaticJointDef.lowerTranslation = 0.0f;
    prismaticJointDef.upperTranslation = 5.0f;
    prismaticJointDef.enableLimit = true;
    world.CreateJoint(&prismaticJointDef);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movingCube.getBody()->ApplyForceToCenter(b2Vec2(0.05f, 0.0f), true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movingCube.getBody()->ApplyForceToCenter(b2Vec2(-0.05f, 0.0f), true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            movingCube.resetPosition();
        }

        world.Step(1 / 60.f, 8, 3);
        anchor.update();
        movingCube.update();

        window.clear();
        anchor.draw(window);
        movingCube.draw(window);
        window.display();
    }

    return 0;
}
