#pragma once
#include <memory>
#include <string>
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class RenderWindow;
    class RectangleShape;
}

class Ball;

class Window
{
public:
    Window(int width = 800, int height = 600, std::string title = "Default");
    
    unsigned int windowWidth;
    
    unsigned int windowHeight;
    
    std::string windowTitle;

    std::shared_ptr<sf::RenderWindow> window;

    std::shared_ptr<sf::RectangleShape> verticalLine;

    std::shared_ptr<sf::RectangleShape> leftLine;

    std::shared_ptr<sf::RectangleShape> rightLine;

    void initialize();

    void drawLines();
    
    bool doesPuckTouchLeftGoal(sf::Vector2f puckPosition);

    bool doesPuckTouchRightGoal(sf::Vector2f puckPosition);
};
