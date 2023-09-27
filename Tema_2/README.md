# Tema 2

## Código

```cpp
#include <Box2D/Box2D.h>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    // Define el vector de la gravedad
    b2Vec2 gravity(0.0f, -1.62f);

    // Se construye un objeto de mundo que contendrá y simulará los cuerpos rígidos
    b2World world(gravity);

    // Se crea un cuerpo dinamico para la bala
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for the bullet
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.1f, 0.03f);

    // Se define otra forma rectangular para la bala
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 7.86f;
    fixtureDef.friction = 0.0f;

    // Sgrega la fotma del cuerpo
    body->CreateFixture(&fixtureDef);

    // Se establece la velocidad inicial de la bala
    float angle = 60.0f; // Angulo en grados
    float speed = 250.0f; // Velocidad en m/s
    float vx = speed * std::cos(angle * M_PI / 180.0f);
    float vy = speed * std::sin(angle * M_PI / 180.0f);

    body->SetLinearVelocity(b2Vec2(vx, vy));

    // Se simula el mundo
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        std::cout << body->GetPosition().x << " " << body->GetPosition().y << std::endl;

    }

    // Se recuerda limpiar 
    world.DestroyBody(body);

    return 0;
}
```

## Explicación/Cambios del código

El código como tal es similar a los anteriores hechos pero con la diferencia de que en vez de simular una caída simulamos el disparo de una bala de cañón en la luna como tal la forma en la que funciona es así.

Los cambios que se hicieron al código fue el de la gravedad para que sea el de la luna ósea 1.62. 

Después en el cuerpo de la bala se le cambiaron la densidad a una menor de la que se tenia en el anterior trabajo (el de Júpiter y el cubo de material muy pesado) y la fricción volvió a 0 ya que como tal en la luna no hay fricción.

Por ultimo se le agregaron los float de velocidad y angle para definir la velocidad a la que la bala de cañón es disparada y a que ángulo se va a simular la trayectoria de la bala en la luna. 

Lo ultimo que se toma en cuenta son estos 2 en particular 
 float vx = speed * std::cos(angle * M_PI / 180.0f); el cual calcula la velocidad inicial usando la funcion coseno para el componente horizontal
 float vy = speed * std::sin(angle * M_PI / 180.0f); el cual calcula la velocidad inicial usando la funcion seno para el componente vertical