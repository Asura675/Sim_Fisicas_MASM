
## Hola Luna

### Código 
```cpp
#include <iostream>
#include <Box2d/Box2d.h>

int main(){
    //Creacion del mundo y de la gravedad
    b2Vec2 gravity(0.0f, -1.62f); //Define la gravedad de la luna
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
    bodyDef.type = b2_dynamicBody; //Cuerpo Dinamico 
    bodyDef.position.Set(0.0f,20.f); //Posicion inicial

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f,1.0f); // Tamaño del cubo

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 0.0f; //No hay friccion en la luna

    body ->CreateFixture(&fixtureDef);

    float timeStep = 1.0f/60.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i=0; i<300; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body -> GetPosition();
        float angle = body-> GetAngle();
        printf("%4.2f %4.2f %4.2f \n", position.x, position.y, angle);
    }
}
```

## Cambios hechos a Hola Mundo

En este código se uso de base el hecho en hola mundo ya que su lógica es la misma aunque con sus pequeños cambios para esta vez hacer una simulación de la caída de un cubo en la luna. Los cambios hechos fueron estos:
1.-Cambio de la gravedad de 9.81 m/s² a 1.62 m/s² (la gravedad que hay en la luna) para simular la caída en la luna.
2.-Cambio en la fricción del cubo a 0 ya que como tal en la luna no se encuentra fricción como lo puede ser en la tierra por el aire.

También se cambio la altura desde la que cae el cubo aunque eso no influye en esta simulación aparte del aumento de iteraciones para ver que sucede si las iteraciones aumentaban por curiosidad de uno en comparación al del anterior código de hola mundo que solo se usaron 60.  

## El por que de haber hecho así el código

La razón por la que se hizo el código de esta manera es mas que nada por pura lógica ya que al basarnos en el código anterior donde tomamos en cuenta la gravedad de la tierra se dio una idea clara de como hacer lo mismo solo que en este caso que el cubo sea afectado por la gravedad lunar e investigar los datos necesarios para simular la caída lunar.
