#pragma once
#include "CircleObject.h"

class Puck: CircleObject
{
public:
    Puck(float radius, int windowX, int windowY, sf::Color color);

    void initialize(sf::Color color);
    
    void placeInCenter();

    void move();

    void implementHit(sf::Vector2f playerPosition, sf::Vector2f playerVelocity ,float playerRadius);
    
    bool isTouchingPlayer(sf::Vector2f playerPos, float playerRadius);
    
    void reset();

    std::shared_ptr<sf::CircleShape> puckShape;

private:
    float puckSpeed = 300;

    float puckRadius;
    
    void handleWallCollision();
    
    sf::Vector2f normalize(const sf::Vector2f& v) const;
    
    float multiplyVectors(sf::Vector2f first, sf::Vector2f second);

    void resolvePenetration(const sf::Vector2f& playerPosition, const sf::Vector2f& normal, float minDistance);
    
    bool isApproaching(float approachSpeed);
    
    sf::Vector2f computeFinalVelocity(const sf::Vector2f& relativeVelocity, const sf::Vector2f& normal,float approachSpeed,const sf::Vector2f& playerVelocity);

    void handleVerticalCollision(sf::Vector2f& pos, sf::Vector2f& dir);
    
    void handleHorizontalCollision(sf::Vector2f& pos, sf::Vector2f& dir);
};