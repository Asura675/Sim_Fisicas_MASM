#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Cube {
public:
    Cube(b2World& world, float x, float y) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        bodydef.type = b2_dynamicBody;
        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(10.f, 10.f));
        box.setFillColor(sf::Color::Blue);
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
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Articulacion Rotacion!");

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    Cube cube1(world, 400, 300);
    Cube cube2(world, 500, 300);

    // Crear un cuerpo intermedio (anclaje) para el joint de revolución
    b2BodyDef anchorDef;
    anchorDef.position.Set(450 / SCALE, 300 / SCALE);
    b2Body* anchor = world.CreateBody(&anchorDef);

    // Crear el joint de revolución entre el anclaje y los cubos
    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.Initialize(anchor, cube1.getBody(), anchor->GetWorldCenter());
    world.CreateJoint(&revoluteJointDef);

    revoluteJointDef.Initialize(anchor, cube2.getBody(), anchor->GetWorldCenter());
    world.CreateJoint(&revoluteJointDef);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            cube1.getBody()->ApplyForceToCenter(b2Vec2(0.05f, 0.0f), true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            cube1.getBody()->ApplyForceToCenter(b2Vec2(-0.05f, 0.0f), true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            cube1.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.05f), true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            cube1.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.05f), true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            cube1.resetPosition();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            cube1.stop();
        }

        world.Step(1 / 60.f, 8, 3);
        cube1.update();
        cube2.update();

        window.clear();
        cube1.draw(window);
        cube2.draw(window);
        window.display();
    }

    return 0;
}
