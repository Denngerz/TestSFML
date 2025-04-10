#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

namespace sf
{
    class RenderWindow;
}

class GameLoop
{
public:
    GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle, sf::Color clearColor);

    std::shared_ptr<sf::RenderWindow> getWindow() const;
    
    void RunLoop();

    void generate();

    void logic();
    
    void getInput();

    void draw();

    bool isEndGame();

    std::shared_ptr<sf::RenderWindow> window;

private:
    sf::Color clearWindowColor;
};
