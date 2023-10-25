#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Articulacion de Engranaje");

    b2Vec2 gravity(0.0f, 9.8f); // Gravedad vertical hacia abajo
    b2World world(gravity);

    b2BodyDef anchor1;
    anchor1.position.Set(300.0f, 20.0f);
    b2Body* anchorPoint = world.CreateBody(&anchor1);

    b2BodyDef anchor2;
    anchor1.position.Set(500.0f, 50.0f);
    b2Body* anchorPoint2 = world.CreateBody(&anchor2);

    // Crear los cuerpos para las ruedas
    b2BodyDef bodyDef1;
    bodyDef1.type = b2_dynamicBody;
    bodyDef1.position.Set(300.0f / SCALE, 300.0f / SCALE);
    b2Body* wheelBody1 = world.CreateBody(&bodyDef1);

    b2BodyDef bodyDef2;
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position.Set(500.0f / SCALE, 300.0f / SCALE);
    b2Body* wheelBody2 = world.CreateBody(&bodyDef2);

    // Crear formas de las ruedas (círculos)
    b2CircleShape wheelShape;
    wheelShape.m_radius = 50.0f / SCALE; // Radio de las ruedas

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wheelShape;
    fixtureDef.density = 1.0f;

    wheelBody1->CreateFixture(&fixtureDef);
    wheelBody2->CreateFixture(&fixtureDef);

    // Crear una articulación de revolución en cada rueda
    b2RevoluteJointDef revoluteJointDef1;
    revoluteJointDef1.Initialize(anchorPoint, wheelBody1, wheelBody1->GetWorldCenter());
    b2RevoluteJoint* revoluteJoint1 = static_cast<b2RevoluteJoint*>(world.CreateJoint(&revoluteJointDef1));

    b2RevoluteJointDef revoluteJointDef2;
    revoluteJointDef2.Initialize(anchorPoint2, wheelBody2, wheelBody2->GetWorldCenter());
    b2RevoluteJoint* revoluteJoint2 = static_cast<b2RevoluteJoint*>(world.CreateJoint(&revoluteJointDef2));

    // Crear una articulación de engranaje
    b2GearJointDef gearJointDef;
    gearJointDef.bodyA = wheelBody1;
    gearJointDef.bodyB = wheelBody2;
    gearJointDef.joint1 = revoluteJoint1;
    gearJointDef.joint2 = revoluteJoint2;
    gearJointDef.ratio = 2.0f * b2_pi; // Ajusta el valor de la proporción según tus necesidades
    world.CreateJoint(&gearJointDef);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar la simulación de Box2D
        world.Step(1.0f / 60.0f, 8, 3);

        // Borrar la ventana
        window.clear();

        // Dibujar las ruedas
        float wheelRadius = 1.0f;
        b2Vec2 wheelPosition1 = wheelBody1->GetPosition();
        sf::CircleShape wheelSFML1(wheelRadius * SCALE);
        wheelSFML1.setFillColor(sf::Color::Yellow);
        wheelSFML1.setOrigin(wheelRadius * SCALE, wheelRadius * SCALE);
        wheelSFML1.setPosition(wheelPosition1.x * SCALE, wheelPosition1.y * SCALE);
        window.draw(wheelSFML1);

        b2Vec2 wheelPosition2 = wheelBody2->GetPosition();
        sf::CircleShape wheelSFML2(wheelRadius * SCALE);
        wheelSFML2.setFillColor(sf::Color::Blue);
        wheelSFML2.setOrigin(wheelRadius * SCALE, wheelRadius * SCALE);
        wheelSFML2.setPosition(wheelPosition2.x * SCALE, wheelPosition2.y * SCALE);
        window.draw(wheelSFML2);

        // Mostrar el contenido en la ventana
        window.display();
    }

    return 0;
}
