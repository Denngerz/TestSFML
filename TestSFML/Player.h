#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(float radius);
    
    std::shared_ptr<sf::CircleShape> mallet;

    sf::Vector2f velocity;

    sf::Vector2f direction;

    void initialize(sf::Color playerColor, int windowX, int windowY, bool startsOnLeft);
    
    void setInnitialPosition(bool startsOnLeft, int windowX, int windowY);

    float malletRadius;

    void move(int windowX, int windowY);

    float speed = 400.0f;

    void tryCorrectPlayerPosition(int windowX, int windowY);
    
    void tryCorrectByWindow(int windowX, int windowY, sf::Vector2f playerPosition);
    
    void tryCorrectByMiddle(int windowX, int windowY, sf::Vector2f playerPosition);
    
    void resetVelocity();

    bool isOnLeft;

    float mass = 300.0f;
};
