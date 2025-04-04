#include "Window.h"

#include <iostream>
#include <SFML/Graphics.hpp>

Window::Window(int width, int height, std::string title)
{
    windowHeight = height;
    windowWidth = width;
    windowTitle = title;
}

void Window::initialize()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode({windowWidth, windowHeight}), windowTitle);

    verticalLine = std::make_shared<sf::RectangleShape>(sf::Vector2f(1.f, static_cast<float>(windowHeight)));
    verticalLine->setFillColor(sf::Color::Black);
    verticalLine->setPosition(sf::Vector2f(static_cast<float>(windowWidth) / 2.f, 0.f));

    leftLine = std::make_shared<sf::RectangleShape>(sf::Vector2f(10.f, static_cast<float>(windowHeight) / 3));
    leftLine->setFillColor(sf::Color::Black);
    leftLine->setPosition(sf::Vector2f(0.f, static_cast<float>(windowHeight) / 3.f));

    rightLine = std::make_shared<sf::RectangleShape>(sf::Vector2f(10.f, static_cast<float>(windowHeight) / 3));
    rightLine->setFillColor(sf::Color::Black);
    rightLine->setPosition(sf::Vector2f(windowWidth - 10, static_cast<float>(windowHeight) / 3.f));
}

void Window::drawLines()
{
    window->draw(*verticalLine);

    window->draw(*leftLine);

    window->draw(*rightLine);
}

bool Window::doesPuckTouchLeftGoal(sf::Vector2f puckPosition)
{
    if(leftLine->getGlobalBounds().contains(puckPosition))
    {
        return true;
    }

    return false;
}

bool Window::doesPuckTouchRightGoal(sf::Vector2f puckPosition)
{
    if(rightLine->getGlobalBounds().contains(puckPosition))
    {
        return true;
    }

    return false;
}
