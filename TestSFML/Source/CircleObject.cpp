#include "CircleObject.h"
#include "../Time/Time.h"

CircleObject::CircleObject(float radius, unsigned int windowWidth, unsigned int windowHeight)
{
    circleRadius = radius;

    circle = std::make_shared<sf::CircleShape>(radius);

    windowX = windowWidth;

    windowY = windowHeight;
}

void CircleObject::initialize(sf::Color color)
{
    circle->setOutlineThickness(3.f);
    circle->setOutlineColor(sf::Color::Black);

    circle->setOrigin({circleRadius, circleRadius});
    circle->setFillColor(color);
}

void CircleObject::move()
{
    velocity = direction * speed * Time::getDeltaTime();
    
    circle->move(velocity);
}

sf::Vector2f CircleObject::getPosition() const
{
    return  circle->getPosition();
}

void CircleObject::setPosition(sf::Vector2f pos)
{
    circle->setPosition(pos);
}

void CircleObject::setDirection(sf::Vector2f dir)
{
    direction = dir;
}

sf::Vector2f CircleObject::getDirection() const
{
    return direction;
}

void CircleObject::setSpeed(float s)
{
    speed = s;
}

float CircleObject::getSpeed() const
{
    return speed;
}

sf::Vector2f CircleObject::getVelocity() const
{
    return velocity;
}

float CircleObject::getRadius() const
{
    return circleRadius;
}

std::shared_ptr<sf::CircleShape> CircleObject::getShape() const
{
    return circle;
}
