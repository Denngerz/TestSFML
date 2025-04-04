#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
    Ball(float radius);
    
    sf::CircleShape* ball;
    
    void initialize(int windowX, int windowY);

    void move(int windowX, int windowY);

    float speed = 200;

    float mass = 10;
    
    void implementHit(sf::Vector2f playerPosition, sf::Vector2f playerVelocity, float playerMalletMass);

    bool isTouching(sf::Vector2f playerPos, float playerRadius);

    void reset(int windowX, int windowY);

private:
    bool isBallOutOfFieldByX(int windowX, int windowY) const;
    
    bool isBallOutOfFieldByY(int windowY) const;
    
    void tryChangeDirrection(bool shouldChangeX, bool shouldChangeY);

    sf::Vector2f velocity;

    sf::Vector2f direction;

    sf::Vector2f normalize(const sf::Vector2f& v);

    float ballRadius = 10.f;
};
