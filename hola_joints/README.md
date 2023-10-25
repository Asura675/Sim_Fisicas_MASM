## VentanaSFML

### Código
```cpp
#include <SFML/Graphics.hpp>  
#include <Box2D/Box2D.h>  
  
```

## Explicación del código

El código utilizado usa la librería SFML en conjunto con Box2D para crear una aplicación de física en 2D la cual representa un cubo que se puede controlar con las teclas del teclado establecidas (W, A, S, D) para aplicar la fuerza y manipular el movimiento .

```cpp
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
```
Como en anteriores códigos trabajados se establecen las bibliotecas que se ocupan para que corra el código aquí se usa SFML para gráficos y eventos mientras que Box2D se usar para la simulación de física en 2D.

```CPP
constexpr float SCALE = 30.0f;
```
Después se define una constante nombrada SCALE para  convertir entre las unidades del mundo en el proyecto con las de nuestra pantalla el cual le otorgamos una de 30 pixeles como se muestra en 30.0f.
```cpp
class Cube {  
public:  
    Cube(b2World &world, float x, float y) {  
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
  
    void draw(sf::RenderWindow &win) const {  
        win.draw(box);  
    }  
  
    void resetPosition() {  
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());  
    }  
  
    void stop() {  
        body->SetLinearVelocity(b2Vec2(0, 0));  
    }  
  
    b2Body *getBody() {  
        return body;  
    }  
  
private:  
    sf::RectangleShape box;  
    b2Body *body;  
};  
```
Aquí en la clase se le define como cubo y se le definen sus propiedades que va a tener en el mundo como su densidad, tamaño, forma y el tipo de cuerpo que será en este caso dinámico. Además de agregarle un color y de donde se va a originar, En pocas palabras representa el cubo al igual que lo crea y actualiza cuando se mueve de posición. 

```cpp
int main() {  
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");  
  
    b2Vec2 gravity(0.0f, 0.0f);  
    b2World world(gravity);  
  
    Cube cube(world, 400, 300);  
  
    while (window.isOpen()) {  
        sf::Event event;  
        while (window.pollEvent(event)) {  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {  
                cube.resetPosition();  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {  
                cube.stop();  
            }  
  
            // The Z key event to close the window  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {  
                window.close();  
                return 0; // return from the main function, effectively ending the program  
            }  
        }  
  
        world.Step(1 / 60.f, 8, 3);  
        cube.update();  
  
        window.clear();  
        cube.draw(window);  
        window.display();  
    }  
    return 0;  
}
```
Ya por ultimo en la función int que es el punto de entrada, se crea la ventana  y configura el mundo físico además de instanciar la clase cubo con lo ya establecido en la clase. Por su parte se pone un bucle while que es el núcleo del programa y se ejecuta mientras la ventana este abierta y ocurre la interacción del usuario con la actualización de la simulación. Por supuesto se agregan las teclas para su debido uso en el movimiento del cubo W moviéndolo arriba, A para la izquierda, S hacia abajo y D hacia la derecha mientras que la tecla R se usa para detenerse de inmediato y la Z para que podamos termina la simulación en otras palabras cerrar la ventana.
## Por que funciona el código

En pocas palabras el código funciona porque se utilizan las capacidades proporcionadas por las bibliotecas SFML y Box2D para lograr una simulación interactiva donde el cubo responde a las acciones del usuario y experimenta la física simulada en tiempo real. Por su parte el bucle principal es lo que asegura que el programa se ejecute continuamente haciendo posible la interacción y actualización de la simulación.