## Hola Polígonos

### Código
```cpp
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
    float timeStep = 1.0f / 60.0f;    
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
```

## Explicación del código

El código comienza importando las librerías necesarias que incluyen `iostream` para la entrada y salida estándar y `Box2D` para la simulación de física.
```cpp
#include <iostream>
#include <Box2D/Box2D.h>
```
Después se configura la física del mundo con una gravedad que actúa hacia abajo  bueno en realidad primero se ocupa el int main que es el punto de entrada para después configurar la física.
```cpp
int main(){
b2Vec2 gravity(0.0f, -9.81f);
b2World world(gravity);
//.....
}
```

A continuación definimos un objeto estático que representara el suelo del mundo y la forma para hacer eso es utilizar `b2BodyDef` para definir las propiedades de este cuerpo, como su posición inicial que en este caso viene siendo `(0.0f, 0.0f)`). Como tal el cuerpo actuará como un suelo inmóvil sobre el cual los objetos interactuarán.
```cpp
b2BodyDef groundBodyDef;
groundBodyDef.position.Set(0.0f, 0.0f);
```
Después se crean formas geométricas para seis figuras diferentes: triángulo, rectángulo, cuadrado, pentágono, hexágono y octágono. Esto se hace para que más adelante en el código se creen sus cuerpos
```cpp
b2PolygonShape triangleShape;  
b2PolygonShape rectangleShape;  
b2PolygonShape squareShape;  
b2PolygonShape pentagonShape;  
b2PolygonShape hexagonShape;  
b2PolygonShape octagonShape;
```
Como consecuente se procede a definir las coordenadas de los vértices de las figuras utilizando arreglos `b2Vec2` para que sean definidas de manera precisa.
```cpp
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
```

Para después de eso se define una `bodyDef` que se utilizará para todos los cuerpos de las figuras. Los cuerpos se crean como cuerpos dinámicos, lo que significa que pueden moverse y responder a fuerzas. Además de que se crean los cuerpos para cada figura usando `world.CreateBody()` y luego se agrega la forma a cada cuerpo con `CreateFixture()`
```cpp
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
```
Luego establecemos los parámetros para la simulación, como el paso de tiempo con `timeStep`, el número de iteraciones de velocidad con `velocityIterations` y el número de iteraciones de posición con `positionIterations`. Y en cada paso de la simulación se llama a `world.Step()` para avanzar la simulación en el tiempo para que luego se imprima la posición de cada cuerpo en ese momento específico, lo que permite rastrear cómo se mueven los objetos a lo largo del tiempo
```cpp
// Definir el tiempo de paso para la simulación  
float timeStep = 1.0f / 60.0f; 
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
```
Ya por ultimo se destruyen los cuerpos creados usando `world.DestroyBody()` para liberar la memoria utilizada por ellos antes de que el programa termine y también el programa devuelve 0 como un indicador de que se ejecutó con éxito.
```cpp
// Se recuerda limpiar  
world.DestroyBody(triangleBody);  
world.DestroyBody(rectangleBody);  
world.DestroyBody(squareBody);  
world.DestroyBody(pentagonBody);  
world.DestroyBody(hexagonBody);  
world.DestroyBody(octagonBody);  
  
return 0;
```

## Por que funciona el código

El código como tal funciona porque se utiliza la biblioteca Box2D que proporciona una infraestructura para simular física en un entorno 2D. En el programa se crea un mundo físico con una gravedad simulada en donde se definen cuerpos geométricos  utilizando la biblioteca. Luego se crean cuerpos físicos para que luego se les asignan las formas geométricas que requerimos  ósea triangulo, cuadrado, rectángulo, pentágono, hexágono y octágono.

En el bucle principal del programa se simula el movimiento de los cuerpos en función del tiempo en donde se utiliza los parámetros de gravedad y las formas anteriormente definidas y en cada iteración del bucle se van calculando las nuevas posiciones de los cuerpos y los resultados se imprimen en la consola.