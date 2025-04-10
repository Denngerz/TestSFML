#pragma once
#include "CircleObject.h"

class Puck: CircleObject
{
public:
    Puck(float radius, float goalTopY, float goalBottomY);

    void initialize(sf::Color color, int windowX, int windowY);
    
    void placeInCenter(int windowX, int windowY);

    void move(int windowX, int windowY);

    void implementHit(sf::Vector2f playerPosition, sf::Vector2f playerVelocity ,float playerRadius);
    
    bool isTouchingPlayer(sf::Vector2f playerPos, float playerRadius);
    
    void reset(int windowX, int windowY);

    std::shared_ptr<sf::CircleShape> puckShape;

private:
    float puckSpeed = 300;

    float goalTop;

    float goalBottom;

    float puckRadius;
    
    void handleWallCollision(int windowX, int windowY);
    
    sf::Vector2f normalize(const sf::Vector2f& v) const;
    
    float multiplyVectors(sf::Vector2f first, sf::Vector2f second);

    void resolvePenetration(const sf::Vector2f& playerPosition, const sf::Vector2f& normal, float minDistance);
    
    bool isApproaching(float approachSpeed);
    
    sf::Vector2f computeFinalVelocity(const sf::Vector2f& relativeVelocity, const sf::Vector2f& normal,float approachSpeed,const sf::Vector2f& playerVelocity);

    void handleVerticalCollision(sf::Vector2f& pos, sf::Vector2f& dir, int windowY);
    
    void handleHorizontalCollision(sf::Vector2f& pos, sf::Vector2f& dir, int windowX);
};