## Hola Júpiter

### Código
```cpp
#include <iostream>
#include <Box2d/Box2d.h>

int main(){
    //Creacion del mundo y de la gravedad
    b2Vec2 gravity(0.0f, -24.79f); //Define la gravedad de Jupiter
    b2World world (gravity);

    //Caracteristicas del cuerpo
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    //Creamos el cuerpo
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    //Crear su forma
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f,1.0f);

    groundBody ->CreateFixture(&groundBox, 0.0f);

    //Creacion del cubo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f,15.0f);

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f,1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 15600.0f;
    fixtureDef.friction = 0.8f;

    body ->CreateFixture(&fixtureDef);

    float timeStep = 1.0f/60.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i=0; i<60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body -> GetPosition();
        float angle = body-> GetAngle();
        printf("%4.2f %4.2f %4.2f \n", position.x, position.y, angle);
    }
}
```

## Cambios hechos al código de Hola Luna

Parecido a lo que ocurrió con Hola Mundo ahora se cambiaron los datos que se habían configurado en hola Luna para poder hacer la simulación de un cubo hecho a base de carburo de tungsteno que pesa 15g/cm3. 

Primero que nada se debió cambiar la gravedad del mundo ya que estamos teniendo una simulación en Júpiter cuya gravedad es de 24.79 m/s² así que pasamos de la gravedad de la luna de 1.62 a la de Júpiter en este código.

Segundo cambiamos la densidad acorde a lo que se estableció para el material del que esta hecho el cubo además de representar un objeto mas denso por la gravedad de Júpiter.

Tercero y ultimo se le agrega una densidad ya que caso contrario con la luna donde no existe fricción, en Júpiter la atmosfera es densa haciendo que ocurra una resistencia al movimiento del cubo. 

## Razón por la que se hizo el código de esa manera

De igual forma con lo que ocurrió en el de la luna se hizo ya que al tener la lógica del código solo era cuestión de modificar ciertos datos para poder hacer la simulación de la física en el cubo solo que esta vez en otro planeta con diferente gravedad. Además de tomar en cuenta el material del que esta hecho el cubo y poner la densidad correcta además de que esta vez la fricción si se toma en cuenta.