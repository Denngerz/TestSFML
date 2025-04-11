#include "Mallet.h"

Mallet::Mallet(float radius, sf::Color color, bool isOnLeft, int windowX, int windowY): CircleObject(radius, windowX, windowY)
{
    malletRadius = radius;
    
    initialize(color, isOnLeft);

    setInitialPosition();
}

void Mallet::initialize(sf::Color color, bool isOnLeft)
{
    CircleObject::initialize(color);

    isMalletOnLeft = isOnLeft;

    malletShape = getShape();

    setInitialPosition();

    setSpeed(malletSpeed);
}

void Mallet::setInitialPosition()
{
    if(isMalletOnLeft)
    {
        malletShape->setPosition(sf::Vector2f(malletRadius, windowY / 2));
    }
    else
    {
        malletShape->setPosition(sf::Vector2f(windowX-malletRadius, windowY / 2));
    }
}

void Mallet::move()
{
    CircleObject::move();

    handleWallCollision();
}

void Mallet::handleWallCollision()
{
    sf::Vector2f pos = getPosition();

    handleVerticalCollision(pos);
    handleHorizontalCollision(pos);

    setPosition(pos);
}

void Mallet::handleVerticalCollision(sf::Vector2f& pos)
{
    if (pos.y - malletRadius < 0.f)
    {
        pos.y = malletRadius;
    }
    else if (pos.y + malletRadius > windowY)
    {
        pos.y = windowY - malletRadius;
    }
}

void Mallet::handleHorizontalCollision(sf::Vector2f& pos)
{
    if (pos.x - malletRadius < 0.f)
    {
        pos.x = malletRadius;
    }
    else if (pos.x + malletRadius > windowX)
    {
        pos.x = windowX - malletRadius;
    }
}

sf::Vector2f Mallet::getVelocity()
{
    return CircleObject::getVelocity();
}

void Mallet::setDirection(sf::Vector2f direction)
{
    CircleObject::setDirection(direction);
}

sf::Vector2f Mallet::getDirection()
{
    return  CircleObject::getDirection();
}
