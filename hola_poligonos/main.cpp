#include <iostream>
#include <Box2D/Box2D.h>

int main() {
    // Crear un mundo de física
    b2Vec2 gravity(0.0f, -9.81f);
    b2World world(gravity);

    // Definir un cuerpo estático en el suelo
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);

    // Crear formas geométricas para las figuras
    b2PolygonShape triangleShape;
    b2PolygonShape rectangleShape;
    b2PolygonShape squareShape;
    b2PolygonShape pentagonShape;
    b2PolygonShape hexagonShape;
    b2PolygonShape octagonShape;

    // Triángulo (equilátero)
    b2Vec2 triangleVertices[3];
    triangleVertices[0].Set(0.0f, 0.0f);
    triangleVertices[1].Set(1.0f, 0.0f);
    triangleVertices[2].Set(0.5f, 1.0f);
    triangleShape.Set(triangleVertices, 3);

    // Rectángulo
    rectangleShape.SetAsBox(1.0f, 0.5f);

    // Cuadrado (igual que el rectángulo pero con lados iguales)
    squareShape.SetAsBox(0.5f, 0.5f);

    // Pentágono
    b2Vec2 pentagonVertices[5];
    pentagonVertices[0].Set(0.0f, 0.0f);
    pentagonVertices[1].Set(1.0f, 0.0f);
    pentagonVertices[2].Set(1.5f, 1.0f);
    pentagonVertices[3].Set(0.5f, 1.5f);
    pentagonVertices[4].Set(-0.5f, 1.0f);
    pentagonShape.Set(pentagonVertices, 5);

    // Hexágono
    b2Vec2 hexagonVertices[6];
    hexagonVertices[0].Set(0.0f, 0.0f);
    hexagonVertices[1].Set(1.0f, 0.0f);
    hexagonVertices[2].Set(1.5f, 1.0f);
    hexagonVertices[3].Set(1.0f, 1.5f);
    hexagonVertices[4].Set(0.0f, 1.5f);
    hexagonVertices[5].Set(-0.5f, 1.0f);
    hexagonShape.Set(hexagonVertices, 6);

    // Octágono
    b2Vec2 octagonVertices[8];
    octagonVertices[0].Set(0.0f, 0.0f);
    octagonVertices[1].Set(1.0f, 0.0f);
    octagonVertices[2].Set(1.5f, 0.5f);
    octagonVertices[3].Set(1.5f, 1.5f);
    octagonVertices[4].Set(1.0f, 2.0f);
    octagonVertices[5].Set(0.0f, 2.0f);
    octagonVertices[6].Set(-0.5f, 1.5f);
    octagonVertices[7].Set(-0.5f, 0.5f);
    octagonShape.Set(octagonVertices, 8);

    // Crear cuerpos y agregar las formas
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2Body* triangleBody = world.CreateBody(&bodyDef);
    triangleBody->CreateFixture(&triangleShape, 1.0f);

    b2Body* rectangleBody = world.CreateBody(&bodyDef);
    rectangleBody->CreateFixture(&rectangleShape, 1.0f);

    b2Body* squareBody = world.CreateBody(&bodyDef);
    squareBody->CreateFixture(&squareShape, 1.0f);

    b2Body* pentagonBody = world.CreateBody(&bodyDef);
    pentagonBody->CreateFixture(&pentagonShape, 1.0f);

    b2Body* hexagonBody = world.CreateBody(&bodyDef);
    hexagonBody->CreateFixture(&hexagonShape, 1.0f);

    b2Body* octagonBody = world.CreateBody(&bodyDef);
    octagonBody->CreateFixture(&octagonShape, 1.0f);

    // Definir el tiempo de paso para la simulación
    float timeStep = 1.0f / 60.0f;  // Asumiendo una frecuencia de 60 Hz
    int32 velocityIterations = 6;  // Número de iteraciones de velocidad
    int32 positionIterations = 2;  // Número de iteraciones de posición

    for (int i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);

        // Imprimir la posición de cada cuerpo en cada paso
        std::cout << "Paso " << i + 1 << ":" << std::endl;
        std::cout << "Triangulo: " << triangleBody->GetPosition().x << " " << triangleBody->GetPosition().y << std::endl;
        std::cout << "Rectangulo: " << rectangleBody->GetPosition().x << " " << rectangleBody->GetPosition().y << std::endl;
        std::cout << "Cuadrado: " << squareBody->GetPosition().x << " " << squareBody->GetPosition().y << std::endl;
        std::cout << "Pentagono: " << pentagonBody->GetPosition().x << " " << pentagonBody->GetPosition().y << std::endl;
        std::cout << "Hexagono: " << hexagonBody->GetPosition().x << " " << hexagonBody->GetPosition().y << std::endl;
        std::cout << "Octagono: " << octagonBody->GetPosition().x << " " << octagonBody->GetPosition().y << std::endl;
    }


    // Se recuerda limpiar
    world.DestroyBody(triangleBody);
    world.DestroyBody(rectangleBody);
    world.DestroyBody(squareBody);
    world.DestroyBody(pentagonBody);
    world.DestroyBody(hexagonBody);
    world.DestroyBody(octagonBody);

    return 0;
}
