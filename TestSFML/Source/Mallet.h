#pragma once
#include "CircleObject.h"

class Mallet: CircleObject
{
public:
    Mallet(float radius, sf::Color color, bool isOnLeft, int windowX, int windowY);

    void initialize(sf::Color color, bool isOnLeft);
    
    void setInitialPosition();

    void move();

    std::shared_ptr<sf::CircleShape> malletShape;

    sf::Vector2f getVelocity();
    
    sf::Vector2f getDirection();

    void setDirection(sf::Vector2f direction);
    
private:
    void handleWallCollision();

    void handleVerticalCollision(sf::Vector2f& pos);
    
    void handleHorizontalCollision(sf::Vector2f& pos);
    
    float malletSpeed = 400;

    bool isMalletOnLeft;

    float malletRadius;
};
