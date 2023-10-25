#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Articulacion de Rueda");

    // Crear el mundo Box2D
    b2Vec2 gravity(0.0f, 9.8f); // Gravedad vertical hacia abajo
    b2World world(gravity);

    // Crear el cuerpo de la rueda
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(400.0f, 300.0f); // Posición inicial
    b2Body* wheelBody = world.CreateBody(&bodyDef);

    // Crear la forma de la rueda
    b2CircleShape wheelShape;
    wheelShape.m_radius = 50.0f; // Radio de la rueda
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wheelShape;
    wheelBody->CreateFixture(&fixtureDef);

    // Velocidad angular de la rueda
    wheelBody->SetAngularVelocity(1.0f); // Radianes por segundo

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

        // Dibujar la rueda
        b2Vec2 wheelPosition = wheelBody->GetPosition();

        // Obtener el radio de la rueda
        float wheelRadius = 0.0f;
        b2Shape* shape = wheelBody->GetFixtureList()->GetShape();
        if (shape->GetType() == b2Shape::e_circle)
        {
            b2CircleShape* circle = dynamic_cast<b2CircleShape*>(shape);
            wheelRadius = circle->m_radius;
        }

        sf::CircleShape wheelSFML(wheelRadius);
        wheelSFML.setFillColor(sf::Color::Yellow);
        wheelSFML.setPosition(wheelPosition.x - wheelRadius, wheelPosition.y - wheelRadius);
        wheelSFML.setRotation(wheelBody->GetAngle() * 180 / b2_pi); // Convertir de radianes a grados
        window.draw(wheelSFML);

        // Mostrar el contenido en la ventana
        window.display();
    }

    return 0;
}
