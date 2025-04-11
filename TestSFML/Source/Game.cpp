#include "Game.h"
#include "InputAction.h"
#include "Mallet.h"
#include "Puck.h"

AirHockeyPlayer::AirHockeyPlayer(int radius, sf::Color color, bool isOnLeft, int windowX, int windowY)
{
    playersMallet = std::make_shared<Mallet>(radius, color, isOnLeft, windowX, windowY);

    inputAction = std::make_shared<InputAction>();
}

bool AirHockeyPlayer::didPlayerWon()
{
    return scoredGoals >= 3;
}

Game::Game():GameLoop(windowWidth, windowHeight, windowTitle, windowBackgroundColor), currentEvent(sf::Event::KeyPressed{})
{
   
}

void Game::generate()
{
    GameLoop::generate();

    generatePlayers();

    generatePuck();
}

void Game::runLoop()
{
    GameLoop::runLoop();   
}

void Game::logic()
{
    GameLoop::logic();

    movePuck();

    sendEventToInputActions();
}

void Game::getInput()
{
    GameLoop::getInput();

    while (const std::optional<sf::Event> event = window->pollEvent())
    {
        currentEvent = *event;
    }
}

bool Game::isEndGame()
{
   return GameLoop::isEndGame() || somePlayerWon();
}

void Game::draw()
{
    GameLoop::draw();
    
    window->draw(*puck->puckShape);
    window->draw(*firstPlayer->playersMallet->malletShape);
    window->draw(*secondPlayer->playersMallet->malletShape);
    
    window->display();
}

void Game::generatePlayers()
{
    firstPlayer = std::make_shared<AirHockeyPlayer>(30, sf::Color::Blue, true, windowWidth, windowHeight);
    
    secondPlayer = std::make_shared<AirHockeyPlayer>(30, sf::Color::Red, false, windowWidth, windowHeight);
}

void Game::generatePuck()
{
    puck = std::make_shared<Puck>(20, windowWidth, windowHeight, sf::Color::White);
}

bool Game::somePlayerWon()
{
    return firstPlayer->didPlayerWon() || secondPlayer->didPlayerWon();
}

void Game::sendEventToInputActions()
{
    firstPlayer->inputAction->HandleEvent(currentEvent);
    
    secondPlayer->inputAction->HandleEvent(currentEvent);
}

void Game::movePuck()
{
    puck->move();
}
