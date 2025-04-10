#pragma once
#include "CircleObject.h"

class Mallet: CircleObject
{
public:
    Mallet(float radius);

    void initialize(sf::Color color, bool isOnLeft, int windowX, int windowY);
    
    void setInitialPosition(int windowX, int windowY);

    void move(int windowX, int windowY);

    std::shared_ptr<sf::CircleShape> malletShape;

    bool isMalletOnLeft;

    float malletRadius;

    void handleWallCollision(int windowX, int windowY);

    void handleVerticalCollision(sf::Vector2f& pos, int windowY);
    
    void handleHorizontalCollision(sf::Vector2f& pos, int windowX);

    sf::Vector2f getVelocity();

    void setDirection(sf::Vector2f direction);

    sf::Vector2f getDirection();

    float malletSpeed = 400;
    
};
