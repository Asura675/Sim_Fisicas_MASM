#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Cube {
public:
    Cube(b2World &world, float x, float y,  const std::string& bodyType, float density) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        // Utiliza un switch para configurar el tipo de cuerpo en función del argumento bodyType
        if (bodyType == "dynamic") {
            bodydef.type = b2_dynamicBody;
        }
        else if (bodyType == "static") {
            bodydef.type = b2_staticBody;
        }
        else if (bodyType == "kinematic") {
            bodydef.type = b2_kinematicBody;
        }
        else {
            // Tipo de cuerpo predeterminado en caso de valor no válido
            bodydef.type = b2_staticBody;
        }
        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
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
class Circle {
public:
    Circle(b2World &world, float x, float y, float radius) {
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / SCALE, y / SCALE);
        bodyDef.type = b2_dynamicBody;
        body = world.CreateBody(&bodyDef);

        b2CircleShape shape;
        shape.m_radius = radius / SCALE;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.5f;

        body->CreateFixture(&fixtureDef);

        circle.setRadius(radius);
        circle.setOrigin(radius, radius);
        circle.setFillColor(sf::Color::Blue);
    }

    void update() {
        circle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        circle.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(circle);
    }

    void applyForce(float forceX, float forceY) {
        body->ApplyForceToCenter(b2Vec2(forceX, forceY), true);
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
    sf::CircleShape circle;
    b2Body *body;
};

class Rectangle {
public:
    Rectangle(b2World &world, float x, float y, float width, float height,float angle, const std::string& bodyType, float density) {
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / SCALE, y / SCALE);
        bodyDef.angle = angle * (b2_pi / 180);
        if (bodyType == "dynamic") {
            bodyDef.type = b2_dynamicBody;
        }
        else if (bodyType == "static") {
            bodyDef.type = b2_staticBody;
        }
        else if (bodyType == "kinematic") {
            bodyDef.type = b2_kinematicBody;
        }
        else {
            // Tipo de cuerpo predeterminado en caso de valor no válido
            bodyDef.type = b2_staticBody;
        }
        body = world.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        body->CreateFixture(&fixtureDef);

        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setOrigin(width / 2, height / 2);
    }

    void update() {
        rectangle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        rectangle.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow& win) const {
        win.draw(rectangle);
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
    sf::RectangleShape rectangle;
    b2Body* body;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Rube Goldberg");

    b2Vec2 gravity(0.0f, 0.1f);
    b2World world(gravity);

    Circle circle(world, 500, 170, 16);
    Rectangle rectangle(world, 380,380, 600, 10,0, "static",0);
    Rectangle rectangle7(world, 500,180, 200, 10,0, "static",0);
    Rectangle rectangle8(world, 500,120, 200, 5,0, "static",0);
    Rectangle rectangle15(world, 335,225, 150, 5,-35, "static",0);
    Rectangle rectangle16(world, 407,70, 100, 5,90, "static",0);
    Rectangle rectangle18(world, 387,800, 100, 5,-40, "static",0);
    Rectangle rectangle19(world, 337,800, 100, 5,40, "static",0);

    //Joint distance
    Rectangle rectangle3(world, 650,380, 10, 15,0, "dynamic",10);
    Rectangle rectangle4(world, 665,380, 10, 15,0, "dynamic",12);

    b2DistanceJointDef distanceJointDef;
    distanceJointDef.Initialize(rectangle4.getBody(), rectangle3.getBody(), rectangle4.getBody()->GetWorldCenter(), rectangle3.getBody()->GetWorldCenter());
    distanceJointDef.length = 10.0f; // Longitud del joint de distancia

    world.CreateJoint(&distanceJointDef);

    //Joint distance 2
    Circle circle2(world, 530, 110, 16);
    Rectangle rectangle13(world, 530,145, 10, 25,0, "dynamic",0.1);
    b2DistanceJointDef distanceJointDef2;
    distanceJointDef2.Initialize(circle2.getBody(), rectangle13.getBody(), circle2.getBody()->GetWorldCenter(), rectangle13.getBody()->GetWorldCenter());
    distanceJointDef2.length = 10.0f; // Longitud del joint de distancia

    world.CreateJoint(&distanceJointDef2);

    //Joint revolute
    Cube cube(world, 100, 320, "static",1);
    Rectangle rectangle2(world, 140,340, 12, 23,0, "dynamic", 5);

    b2RevoluteJointDef jointDef;
    jointDef.Initialize(cube.getBody(), rectangle2.getBody(), cube.getBody()->GetWorldCenter());
    jointDef.lowerAngle = -0.25f * b2_pi;
    jointDef.upperAngle = 0.25f * b2_pi;
    jointDef.enableMotor = true;
    jointDef.motorSpeed = -0.60f;
    jointDef.maxMotorTorque = 2500.0f;
    world.CreateJoint(&jointDef);

    //Joint revolute 2
    Cube cube4(world, 640, 430, "static",1);
    Rectangle rectangle17(world, 660,430, 10, 13,0, "dynamic", 5);

    b2RevoluteJointDef jointrevDef;
    jointrevDef.Initialize(cube4.getBody(), rectangle17.getBody(), cube4.getBody()->GetWorldCenter());
    jointrevDef.lowerAngle = -0.25f * b2_pi;
    jointrevDef.upperAngle = 0.25f * b2_pi;
    jointrevDef.enableMotor = true;
    jointrevDef.motorSpeed = 0.60f;
    jointrevDef.maxMotorTorque = 2500.0f;
    world.CreateJoint(&jointrevDef);

    //joint pulley
    Rectangle rectangle5(world, 725,600, 80, 10,0, "dynamic",5);
    Rectangle rectangle6(world, 625,600, 50, 10, 0, "dynamic",5);
    Rectangle rectangle11(world, 725,700, 50, 10,0, "static",0);
    Rectangle rectangle12(world, 625,700, 50, 10,0, "static",0);
    Cube cube2(world, 625,460, "dynamic",20);
    b2PulleyJointDef jointPulley;
    jointPulley.Initialize(rectangle5.getBody(),rectangle6.getBody(),rectangle11.getBody()->GetWorldCenter(),rectangle12.getBody()->GetWorldCenter(),rectangle5.getBody()->GetWorldCenter(),rectangle6.getBody()->GetWorldCenter(), 1);
    world.CreateJoint(&jointPulley);

    Rectangle rectangle9(world, 725,480, 80, 10,0, "dynamic",1.1);
    Rectangle rectangle10(world, 625,580, 50, 10,0, "dynamic",0.1);
    b2PrismaticJointDef prismaticJointDef2;
    prismaticJointDef2.Initialize(rectangle9.getBody(), rectangle11.getBody(), rectangle9.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
    prismaticJointDef2.lowerTranslation = -15.0f;
    prismaticJointDef2.upperTranslation = 15.0f;
    prismaticJointDef2.enableLimit = true;
    world.CreateJoint(&prismaticJointDef2);

    b2PrismaticJointDef prismaticJointDef3;
    prismaticJointDef3.Initialize(rectangle10.getBody(), rectangle12.getBody(), rectangle10.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
    prismaticJointDef3.lowerTranslation = -15.0f;
    prismaticJointDef3.upperTranslation = 15.0f;
    prismaticJointDef3.enableLimit = true;
    world.CreateJoint(&prismaticJointDef3);

    //Joint Prismatic
    Cube cube3(world, 620,105, "static",0);
    Rectangle rectangle14(world, 600,95, 10, 25,0, "dynamic",5);
    b2PrismaticJointDef prismaticJointDef;
    prismaticJointDef.Initialize(rectangle14.getBody(), cube3.getBody(), cube3.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0));
    prismaticJointDef.lowerTranslation = -15.0f;
    prismaticJointDef.upperTranslation = 15.0f;
    prismaticJointDef.enableLimit = true;
    prismaticJointDef.enableMotor = true;
    prismaticJointDef.motorSpeed = 0.3f;
    prismaticJointDef.maxMotorForce = 1.0f;
    world.CreateJoint(&prismaticJointDef);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // The Z key event to close the window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                window.close();
                return 0; // return from the main function, effectively ending the program
            }
        }

        world.Step(1 / 60.f, 8, 3);


        cube.update();
        cube2.update();
        cube3.update();
        cube4.update();
        circle.update();
        circle2.update();
        rectangle.update();
        rectangle2.update();
        rectangle3.update();
        rectangle4.update();
        rectangle5.update();
        rectangle6.update();
        rectangle7.update();
        rectangle8.update();
        rectangle9.update();
        rectangle10.update();
        rectangle11.update();
        rectangle12.update();
        rectangle13.update();
        rectangle14.update();
        rectangle15.update();
        rectangle16.update();
        rectangle17.update();
        rectangle18.update();
        rectangle19.update();

        window.clear();
        cube.draw(window);
        cube2.draw(window);
        cube3.draw(window);
        cube4.draw(window);
        circle.draw(window);
        circle2.draw(window);
        rectangle.draw(window);
        rectangle2.draw(window);
        rectangle3.draw(window);
        rectangle4.draw(window);
        rectangle5.draw(window);
        rectangle6.draw(window);
        rectangle7.draw(window);
        rectangle8.draw(window);
        rectangle9.draw(window);
        rectangle10.draw(window);
        rectangle11.draw(window);
        rectangle12.draw(window);
        rectangle13.draw(window);
        rectangle14.draw(window);
        rectangle15.draw(window);
        rectangle16.draw(window);
        rectangle17.draw(window);
        rectangle18.draw(window);
        rectangle19.draw(window);
        window.display();
    }
    return 0;
}