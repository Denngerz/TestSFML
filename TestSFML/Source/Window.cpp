#include "Window.h"
#include <SFML/Graphics.hpp>

void Goal::initializeGoal(float windowWidth, float windowHeight, float goalTopY, float length, float width)
{
    this->goalWidth = width;
    this->goalLength = length;

    this->goalShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(this->goalWidth, this->goalLength));
    this->goalShape->setFillColor(sf::Color::Black);
    this->goalShape->setOrigin(sf::Vector2f(this->goalWidth / 2, this->goalLength / 2));
}

void Goal::placeGoal(float windowWidth, float windowHeight, bool isOnRight)
{
    if (!isOnRight)
    {
        this->goalShape->setPosition(sf::Vector2f(this->goalWidth / 2, windowHeight / 2));
    }
    else
    {
        this->goalShape->setPosition(sf::Vector2f(windowWidth - (this->goalWidth / 2), windowHeight / 2));
    }
}

Window::Window(int width, int height, std::string title)
{
    windowHeight = height;
    windowWidth = width;
    windowTitle = title;

    goalLength = windowHeight / 3;
    goalWidth = 15;
}

void Window::initialize()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode({windowWidth, windowHeight}), windowTitle);

    window->setFramerateLimit(60);

    verticalLine = std::make_shared<sf::RectangleShape>(sf::Vector2f(1.f, windowHeight));
    verticalLine->setFillColor(sf::Color::Black);
    verticalLine->setPosition(sf::Vector2f(windowWidth / 2.f, 0.f));

    leftGoal = std::make_shared<Goal>();
    leftGoal->initializeGoal(windowWidth, windowHeight, goalTopPositionY, goalLength, goalWidth);
    leftGoal->placeGoal(windowWidth, windowHeight, false);

    rightGoal = std::make_shared<Goal>();
    rightGoal->initializeGoal(windowWidth, windowHeight, goalTopPositionY, goalLength, goalWidth);
    rightGoal->placeGoal(windowWidth, windowHeight, true);

    goalTopPositionY = leftGoal->goalShape->getPosition().y - goalLength / 2;
}

void Window::drawLines()
{
    window->draw(*verticalLine);

    window->draw(*leftGoal->goalShape);

    window->draw(*rightGoal->goalShape);
}

bool Window::doesPuckTouchLeftGoal(sf::Vector2f puckPosition)
{
    if(leftGoal->goalShape->getGlobalBounds().contains(puckPosition))
    {
        return true;
    }

    return false;
}

bool Window::doesPuckTouchRightGoal(sf::Vector2f puckPosition)
{
    if(rightGoal->goalShape->getGlobalBounds().contains(puckPosition))
    {
        return true;
    }

    return false;
}
