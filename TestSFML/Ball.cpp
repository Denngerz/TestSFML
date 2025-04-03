#include "Ball.h"
#include "Time.h"

Ball::Ball(float radius)
{
    ballRadius = radius;
}

void Ball::initialize(int windowX, int windowY)
{
    ball = new sf::CircleShape(ballRadius);
    
    ball->setFillColor(sf::Color::White);
    ball->setOutlineThickness(3.f);
    ball->setOutlineColor(sf::Color::Black);
    ball->setOrigin({ballRadius, ballRadius});
    ball->setPosition({windowX / 2.f, windowY / 2.f});
    
    direction = sf::Vector2f(1.0f, 0.0f);
}

void Ball::move(int windowX, int windowY)
{
    velocity = direction * Time::deltaTime * speed; 
    
    ball->move(velocity);

    tryChangeDirrection(isBallOutOfFieldByX(windowX), isBallOutOfFieldByY(windowY));
}

bool Ball::isBallOutOfFieldByX(int windowX) const
{
    float x = ball->getPosition().x;
    return (x - ballRadius <= 0.f) || (x + ballRadius >= static_cast<float>(windowX));
}

bool Ball::isBallOutOfFieldByY(int windowY) const
{
    float y = ball->getPosition().y;
    return (y - ballRadius <= 0.f) || (y + ballRadius >= static_cast<float>(windowY));
}

void Ball::tryChangeDirrection(bool shouldChangeX, bool shouldChangeY)
{
    if(shouldChangeX)
    {
        direction.x = -direction.x;
    }
    if(shouldChangeY)
    {
        direction.y = -direction.y;
    }
}

void Ball::implementHit(sf::Vector2f playerPosition, sf::Vector2f playerVelocity, float playerMalletMass)
{
    sf::Vector2f puckPosition = ball->getPosition();
    
    sf::Vector2f collisionNormal = normalize(puckPosition - playerPosition);
    
    float puckVelocityAlongNormal = velocity.x * collisionNormal.x + velocity.y * collisionNormal.y;
    float playerVelocityAlongNormal = playerVelocity.x * collisionNormal.x + playerVelocity.y * collisionNormal.y;

    float deltaVelocity = playerVelocityAlongNormal - puckVelocityAlongNormal;
    
    sf::Vector2f newVelocity = collisionNormal * deltaVelocity;

    direction = normalize(newVelocity);
    
    speed = newVelocity.length() / Time::deltaTime;
}

sf::Vector2f Ball::normalize(const sf::Vector2f& v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    
    if (length != 0)
    {
        return v / length;
    }
    
    return sf::Vector2f(0.f, 0.f);
}

bool Ball::isTouching(sf::Vector2f playerPos, float playerRadius)
{
    sf::Vector2f delta = ball->getPosition() - playerPos;
    
    float distanceSquared = delta.x * delta.x + delta.y * delta.y;
    
    float combinedRadius = ballRadius + playerRadius;

    return distanceSquared <= combinedRadius * combinedRadius;
}