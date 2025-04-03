#pragma once
#include <memory>
#include <string>

namespace sf
{
    class RenderWindow;
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

    void initialize();
};
