#include "Window.h"
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
}