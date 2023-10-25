## hola_joints

### Códigos
### Distancia
```cpp
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
        box.setFillColor(sf::Color::Red);  
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
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Articulacion Distancia");  
  
    b2Vec2 gravity(0.0f, 0.0f);  
    b2World world(gravity);  
  
    Cube cube1(world, 400, 300);  
    Cube cube2(world, 500, 300); // Crear un segundo cubo  
  
    // Crear el joint de distancia para conectar los cubos    b2DistanceJointDef distanceJointDef;  
    distanceJointDef.Initialize(cube1.getBody(), cube2.getBody(), cube1.getBody()->GetWorldCenter(), cube2.getBody()->GetWorldCenter());  
    distanceJointDef.length = 2.0f; // Longitud del joint de distancia  
  
    world.CreateJoint(&distanceJointDef);  
  
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
        cube2.update(); // Actualizar el segundo cubo  
  
        window.clear();  
        cube1.draw(window);  
        cube2.draw(window); // Dibujar el segundo cubo  
        window.display();  
    }  
    return 0;  
}
  
```
### Rotacion
```cpp
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
```
### Prismática
```cpp
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
```
### Engrane
```cpp 
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
```
### Soldadura
```cpp
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
```
### Rueda
```cpp
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
```
## Explicación de los códigos

Empezando por el código de distancia en si lo que hace es crear una simulación en la que dos cubos que están conectados por una articulación de distancia en un entorno Box2D y se renderiza la simulación en una ventana de SFML.  Como tal el usuario puede mover los cubos con las teclas WASD además de regresar a su posición inicial presionando la barra de espacio (muy similar al código de ejemplo usado en la tarea de Ventana SFML). En si lo que hace la articulación de distancia es limitar la distancia entre los dos cubos.

Pasando ahora al código de Rotación lo que hace es crear una simulación en donde dos cubos en la cual están conectados a un mismo anclaje en donde usando las teclas WASD haciendo que giren alrededor de un punto en común que siendo sincero parece simulación de reloj pero de péndulo al mismo tiempo ya que al chocar rebotan un poco los cubos.

Tercer código siendo el de prismático se vuelven a usar 2 cubos en los cuales están conectados a un anclaje  por medio de la articulación primatica y pues lo que hace es que uno de los cubos se pueda mover horizontalmente con las teclas A y D pero es restringido por la articulación al limitar su movimiento a lo largo de un eje.

Cuarto código siendo el de engranaje se hace la simulación de dos ruedas conectadas a por una articulación de engranaje y lo que hace es que estén conectadas y giren de manera que sus formas angulares se relacionen entre si....bueno eso deberían hacer pero se quedan sin poder moverse (tendré mi venganza gear joint).

Penúltimo código siendo el de soldadura lo que hace es crear un bloque rectangular soldado en su lugar de entorno el entorno de Box2d. Como tal no puede no puede hacer un movimiento al estar sujeto a su posición original todo gracias al joint de soldadura.

Ultimo código el de la articulación de la rueda y lo que hace es crear una rueda giratoria que pues como tal gira continuamente debido a su velocidad angular
## Por que funcionan el códigos 

Las razones por la que funcionan los códigos (en su mayoría) son las siguientes :

1. **Box2D**: Siendo la biblioteca que se encarga de hacer las simulaciones de física como lo son las colisiones y movimientos. Ademas que se utiliza para definir cómo los objetos se comportan en el mundo virtual siguiendo las leyes de la física para poder tener simulaciones en tiempo real.
    
2. **SFML**: Lo que hace la ventana de Sfml es manejar la ventana de visualización y permite que el usuario interactúe con el programa además de encargarse de mostrar los objetos creados con Box2D en una ventana y de capturar eventos como pulsaciones de teclas o de mouse si es que se indica.
    

Lo que se puede concluir es que la interacción entre Box2D y SFML se logra al actualizar la simulación física con Box2D y dibujar los objetos en la ventana de SFML. Básicamente es un dúo dinámico/tag team donde Box2D hace los cálculos de física y SFML se encarga de mostrar esos cálculos y permite al usuario interactuar con ellos.