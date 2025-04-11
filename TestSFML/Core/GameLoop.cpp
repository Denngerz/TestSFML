#include "GameLoop.h"

#include <iostream>

#include "../Time/Time.h"

GameLoop::GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle, sf::Color clearColor)
{
    Time::init();

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode({windowWidth, windowHeight}), windowTitle);

    window->setFramerateLimit(60);

    clearWindowColor = clearColor;
}

void GameLoop::runLoop()
{
    generate();

    while(!isEndGame())
    {
        getInput();
        logic();
        draw();
    }

    std::cout << isEndGame() << std::endl;
}

void GameLoop::generate()
{
}

void GameLoop::logic()
{
    Time::update();
}

void GameLoop::getInput()
{
}

void GameLoop::draw()
{
    window->clear(clearWindowColor);
}

bool GameLoop::isEndGame()
{
    while(const std::optional event = window->pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            std::cout << "Closing..." << std::endl;
            return true;
        }
        return false;
    }
}

std::shared_ptr<sf::RenderWindow> GameLoop::getWindow() const
{
    return window;
}
