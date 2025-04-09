#include "Mallet.h"

Mallet::Mallet(float radius): CircleObject(radius)
{
    malletRadius = radius;
}

void Mallet::initialize(sf::Color color, bool isOnLeft, int windowX, int windowY)
{
    CircleObject::initialize(color);

    isMalletOnLeft = isOnLeft;

    malletShape = CircleObject::getShape();

    setInitialPosition(windowX, windowY);
}

void Mallet::setInitialPosition(int windowX, int windowY)
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

void Mallet::move(int windowX, int windowY)
{
    CircleObject::move();

    handleWallCollision(windowX, windowY);
}

void Mallet::handleWallCollision(int windowX, int windowY)
{
    sf::Vector2f pos = getPosition();

    handleVerticalCollision(pos, windowY);
    handleHorizontalCollision(pos, windowX);

    setPosition(pos);
}

void Mallet::handleVerticalCollision(sf::Vector2f& pos, int windowY)
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

void Mallet::handleHorizontalCollision(sf::Vector2f& pos, int windowX)
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
