#include "Player.h"
#include "Time.h"

Player::Player(float radius)
{
    malletRadius = radius;
}

void Player::initialize(sf::Color playerColor, int windowX, int windowY, bool startsOnLeft)
{
    mallet = std::make_shared<sf::CircleShape>(malletRadius);

    isOnLeft = startsOnLeft;

    mallet->setFillColor(playerColor);
    mallet->setOutlineThickness(3.f);
    mallet->setOutlineColor(sf::Color::Black);
    mallet->setOrigin({malletRadius, malletRadius});

    setInnitialPosition(isOnLeft, windowX, windowY);
    
    direction = sf::Vector2f(1.0f, 1.0f);
}

void Player::setInnitialPosition(bool startsOnLeft, int windowX, int windowY)
{
    if(startsOnLeft)
    {
        mallet->setPosition({malletRadius, windowY / 2.f});
    }
    else
    {
        mallet->setPosition({windowX - malletRadius, windowY / 2.f});
    }
}

void Player::move(int windowX, int windowY)
{
    velocity = direction * speed * Time::getDeltaTime();
    
    mallet->move(velocity);

    tryCorrectPlayerPosition(windowX, windowY);
}

void Player::tryCorrectPlayerPosition(int windowX, int windowY)
{
    sf::Vector2f playerPosition = mallet->getPosition();
    
    tryCorrectByWindow(windowX, windowY, playerPosition);

    tryCorrectByMiddle(windowX, windowY, playerPosition);    
}

void Player::tryCorrectByWindow(int windowX, int windowY, sf::Vector2f playerPosition)
{
    if(mallet->getPosition().y + malletRadius > windowY)
    {
        mallet->setPosition({playerPosition.x, windowY - malletRadius});
    }

    if(mallet->getPosition().y - malletRadius < 0)
    {
        mallet->setPosition({playerPosition.x, malletRadius});
    }

    if(mallet->getPosition().x + malletRadius > windowX)
    {
        mallet->setPosition({windowX - malletRadius, playerPosition.y});
    }

    if(mallet->getPosition().x - malletRadius < 0)
    {
        mallet->setPosition({malletRadius, playerPosition.y});
    }
}

void Player::tryCorrectByMiddle(int windowX, int windowY, sf::Vector2f playerPosition)
{
    if(isOnLeft && mallet->getPosition().x + malletRadius > (windowX/2.f))
    {
        mallet->setPosition({(windowX/2.f) - malletRadius, playerPosition.y});
    }
    
    if(!isOnLeft && mallet->getPosition().x - malletRadius < (windowX/2.f))
    {
        mallet->setPosition({(windowX/2.f) + malletRadius, playerPosition.y});
    }
}

void Player::resetVelocity()
{
    velocity = sf::Vector2f(0.0f, 0.0f);
}