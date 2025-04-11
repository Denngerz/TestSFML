#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class CircleObject
{
public:
    CircleObject(float radius, unsigned int windowWidth, unsigned int windowHeight);
    
    void initialize(sf::Color color);

    void move();
    
    sf::Vector2f getPosition() const;
    
    void setPosition(sf::Vector2f pos);
    
    void setDirection(sf::Vector2f dir);
    
    sf::Vector2f getDirection() const;
    
    void setSpeed(float s);
    
    float getSpeed() const;
    
    sf::Vector2f getVelocity() const;
    
    float getRadius() const;

    std::shared_ptr<sf::CircleShape> getShape() const;

    int windowX;

    int windowY;
        
    float speed;

private:
    std::shared_ptr<sf::CircleShape> circle;
    
    sf::Vector2f velocity;

    sf::Vector2f direction;
    
    float circleRadius;
};
