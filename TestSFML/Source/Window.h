#pragma once
#include <memory>
#include <string>
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class RenderWindow;
    class RectangleShape;
}

struct Goal
{
    std::shared_ptr<sf::RectangleShape> goalShape;

    float goalLength;

    float goalWidth;

    void initializeGoal(float windowWidth, float windowHeight, float goalTopY, float length, float width);

    void placeGoal(float windowWidth, float windowHeight, bool isOnRight);
};

class Window
{
public:
    Window(int width = 800, int height = 600, std::string title = "Default");
    
    unsigned int windowWidth;
    
    unsigned int windowHeight;
    
    std::string windowTitle;

    std::shared_ptr<sf::RenderWindow> window;

    std::shared_ptr<sf::RectangleShape> verticalLine;

    std::shared_ptr<Goal> leftGoal;

    std::shared_ptr<Goal> rightGoal;

    void initialize();

    void drawLines();
    
    bool doesPuckTouchLeftGoal(sf::Vector2f puckPosition);

    bool doesPuckTouchRightGoal(sf::Vector2f puckPosition);

    float goalTopPositionY;

    float goalLength;

    float goalWidth;
};
