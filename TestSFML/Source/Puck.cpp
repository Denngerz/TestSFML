﻿#include "Puck.h"

Puck::Puck(float radius, float goalTopY, float goalBottomY): CircleObject(radius)
{
    goalTop = goalTopY;

    goalBottom = goalBottomY;

    puckRadius = radius;
}

void Puck::initialize(sf::Color color, int windowX, int windowY)
{
    CircleObject::initialize(color);

    puckShape = getShape();

    placeInCenter(windowX, windowY);

    setSpeed(puckSpeed);

    setDirection(sf::Vector2f(1.f, 1.f));
}

void Puck::placeInCenter(int windowX, int windowY)
{
    setPosition(sf::Vector2f(windowX / 2, windowY / 2));
}

void Puck::move(int windowX, int windowY)
{
    CircleObject::move();

    handleWallCollision(windowX, windowY);
}

void Puck::handleWallCollision(int windowX, int windowY)
{
    sf::Vector2f pos = getPosition();
    sf::Vector2f dir = getDirection();

    handleVerticalCollision(pos, dir, windowY);
    handleHorizontalCollision(pos, dir, windowX);

    setPosition(pos);
    setDirection(dir);
}


void Puck::handleVerticalCollision(sf::Vector2f& pos, sf::Vector2f& dir, int windowY)
{
    if (pos.y - puckRadius < 0.f)
    {
        pos.y = puckRadius;
        dir.y *= -1.f;
    }
    else if (pos.y + puckRadius > windowY)
    {
        pos.y = windowY - puckRadius;
        dir.y *= -1.f;
    }
}

void Puck::handleHorizontalCollision(sf::Vector2f& pos, sf::Vector2f& dir, int windowX)
{
    bool isInGoalZone = pos.y - puckRadius > goalTop && pos.y + puckRadius < goalBottom;

    if (isInGoalZone)
    {
        return;
    }

    if (pos.x - puckRadius < 0.f)
    {
        pos.x = puckRadius;
        dir.x *= -1.f;
    }
    else if (pos.x + puckRadius > windowX)
    {
        pos.x = windowX - puckRadius;
        dir.x *= -1.f;
    }
}

bool Puck::isTouchingPlayer(sf::Vector2f playerPos, float playerRadius)
{
    sf::Vector2f delta = getPosition() - playerPos;
    
    float distanceSquared = delta.x * delta.x + delta.y * delta.y;
    
    float combinedRadius = puckRadius + playerRadius;

    return distanceSquared <= combinedRadius * combinedRadius;
}

void Puck::reset(int windowX, int windowY)
{
    placeInCenter(windowX, windowY);

    speed = 100;
}

void Puck::implementHit(sf::Vector2f playerPosition, sf::Vector2f playerVelocity, float playerRadius)
{
    sf::Vector2f puckPosition = getPosition();
    sf::Vector2f delta = puckPosition - playerPosition;
    sf::Vector2f puckVelocity = getVelocity();
    sf::Vector2f relativeVelocity = puckVelocity - playerVelocity;
    
    float minDistance = puckRadius + playerRadius;
    
    sf::Vector2f collisionNormal = normalize(delta);
    resolvePenetration(playerPosition, collisionNormal, minDistance);

    float approachSpeed = multiplyVectors(relativeVelocity, collisionNormal);
    if (!isApproaching(approachSpeed))
    {
        return;
    }

    sf::Vector2f finalVelocity = computeFinalVelocity(relativeVelocity, collisionNormal, approachSpeed, playerVelocity);

    setDirection(normalize(finalVelocity));
    setSpeed(finalVelocity.length() * 30);
}

//===========Help functions===========

sf::Vector2f Puck::normalize(const sf::Vector2f& v) const
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    
    return (length != 0) ? v / length : sf::Vector2f(0.f, 0.f);
}

float Puck::multiplyVectors(sf::Vector2f first, sf::Vector2f second)
{
    return first.x * second.x + first.y * second.y;
}

void Puck::resolvePenetration(const sf::Vector2f& playerPosition, const sf::Vector2f& normal, float minDistance)
{
    setPosition(playerPosition + normal * minDistance);
}

bool Puck::isApproaching(float approachSpeed)
{
    return approachSpeed < 0.f;
}

sf::Vector2f Puck::computeFinalVelocity(const sf::Vector2f& relativeVelocity, const sf::Vector2f& normal, float approachSpeed, const sf::Vector2f& playerVelocity)
{
    sf::Vector2f reflected = relativeVelocity - 2.f * approachSpeed * normal;
    return reflected * 0.6f + playerVelocity;
}