## Hola Mundo

### Código

```cpp
#include <iostream>
#include <Box2d/Box2d.h>

int main(){
    //Creacion del mundo y de la gravedad
    b2Vec2 gravity(0.0f, -9.81f);
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
    bodyDef.position.Set(0.0f,20.f);

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f,1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

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

## Explicación de Código

El código como tal se trata de una pequeña simulación de un cubo cayendo desde cierta altura y se empieza creando un mundo de física bidimensional además de configurar la gravedad de la tierra que es 9.81 m/s² .  Para después crear en la parte inferior del mundo un suelo estático en donde el objeto puede reposar aunque en nuestro caso. Después procedemos ahora a crear nuestra figura/objeto siendo el cubo el cual es creado en el centro del mundo además de que se le configura para que responda a la gravedad establecida de la Tierra a inicios del código. Como siguiente paso se establecen las características del cubo como su densidad y fricción. Ya por ultimo se simula la física de la caída del cubo en 60 iteraciones en donde el mundo se va actualizando obteniendo la posición de en la que se encuentra el cubo. 

## El por que funciona el código

El código logra funcionar de manera correcta ya que la gravedad configurada hace caiga el cubo hacia abajo simulando el efecto que existe en la vida real en la tierra y pues cae por el efecto de la fuerza natural que atrae objetos hacia otros que tienen masa y en eso nos basamos para el uso de la densidad en el cubo ya que si ponemos una mayor densidad haría que la masa del cubo fuese mayor influyendo a su repuesta en la gravedad. La fricción que se configuro al cubo hace que su velocidad de movimiento sea afectada ya que es una fuerza resistiva al movimiento relativo entre dos superficies así que en nuestro código se le puso fricción considerable aunque a mayor fricción mas lento se volvería el descenso del cubo.