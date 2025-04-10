#include "Game.h"
#include "../Source/Window.h"
#include <SFML/Graphics.hpp>
#include "../Source/InputAction.h"
#include "../Source/Mallet.h"
#include "../Source/Time.h"
#include "../Source/Puck.h"

Game::Game()
{
}

void Game::startGame()
{
    generate();

    while(!isEndGame())
    {
        getInput();
        logic();
        draw();
    }
}

void Game::generate()
{
    generateWindow();
    
    generateHockeyPuck();
    
    generatePlayers();

    generateTimer();
}

void Game::getInput()
{
   while(const std::optional event = window->pollEvent())
   {
       if(event->is<sf::Event::KeyPressed>())
       {
           inputAction->HandleEvent(*event);
       }
   }
}

void Game::logic()
{
    Time::update();
        
    movePuck();

    movePlayers();

    tryHandleHit();

    tryHandleGoal();

    tryRestartRound();
}

void Game::draw()
{
    window->clear(sf::Color::Green);

    gameWindow->drawLines();
    
    window->draw(*hockeyPuck->puckShape);
    window->draw(*firstPlayer->mallet);
    window->draw(*secondPlayer->mallet);
    
    window->display();
}

void Game::handleHit(AirHockeyPlayer& player)
{
    hockeyPuck->implementHit(player.mallet->getPosition(), player.player->getVelocity(), player.player->malletRadius);
}

bool Game::isPlayerTouchingPuck(AirHockeyPlayer& player)
{
    return hockeyPuck->isTouchingPlayer(player.mallet->getPosition(), player.mallet->getRadius());
}

void Game::tryHandleHit()
{
    if(isPlayerTouchingPuck(*firstPlayer))
    {
        handleHit(*firstPlayer);
        return;
    }
    
    if(isPlayerTouchingPuck(*secondPlayer))
    {
        handleHit(*secondPlayer);
    }
}

void Game::handleGoal(AirHockeyPlayer& scoredPlayer)
{
    scoredPlayer.score++;
}

void Game::tryHandleGoal()
{
    if(didPuckTouchLeftGoal())
    {
        handleGoal(*secondPlayer);
        shouldRestart = true;
    }
    if(didPuckTouchRightGoal())
    {
        handleGoal(*firstPlayer);
        shouldRestart = true;
    }
}

void Game::tryRestartRound()
{
    if(shouldRestart)
    {
        shouldRestart = false;
        restartRound();
    }
}

bool Game::didPuckTouchLeftGoal()
{
    return gameWindow->doesPuckTouchLeftGoal(hockeyPuck->puckShape->getPosition());
}

bool Game::didPuckTouchRightGoal()
{
    return gameWindow->doesPuckTouchRightGoal(hockeyPuck->puckShape->getPosition());
}

void Game::restartRound()
{
    hockeyPuck->reset(window->getSize().x, window->getSize().y);
}

void Game::generateWindow()
{
    gameWindow = new Window(800, 600, "AirHockey");

    gameWindow->initialize();

    window = gameWindow->window;
}

void Game::movePlayers()
{
    firstPlayer->player->move(window->getSize().x, window->getSize().y);
    secondPlayer->player->move(window->getSize().x, window->getSize().y);
}

void Game::generateHockeyPuck()
{
    hockeyPuck = std::make_shared<Puck>(20, gameWindow->goalTopPositionY, gameWindow->goalTopPositionY + gameWindow->goalLength);

    hockeyPuck->initialize(sf::Color::White, window->getSize().x, window->getSize().y);
}

void Game::generatePlayers()
{
    initializePlayers();

    generatePlayersBindings();
}

void Game::generateTimer()
{
    Time::init();
}

bool Game::isEndGame()
{
    if(firstPlayer->score >= 3 || secondPlayer->score >= 3)
    {
        return true;
    }
    while(const std::optional event = window->pollEvent())
    {
        return event->is<sf::Event::Closed>();
    }
}

void Game::generatePlayersBindings()
{
    inputAction = std::make_shared<InputAction>();

    inputAction->BindKey(sf::Keyboard::Key::W, "W");
    inputAction->BindKey(sf::Keyboard::Key::S, "S");
    inputAction->BindKey(sf::Keyboard::Key::A, "A");
    inputAction->BindKey(sf::Keyboard::Key::D, "D");

    inputAction->BindKey(sf::Keyboard::Key::I, "I");
    inputAction->BindKey(sf::Keyboard::Key::K, "K");
    inputAction->BindKey(sf::Keyboard::Key::J, "J");
    inputAction->BindKey(sf::Keyboard::Key::L, "L");
    
    inputAction->BindAction("W",    [this]() { firstPlayer->player->setDirection({firstPlayer->player->getDirection().x, -1.f}); });
    inputAction->BindAction("S",  [this]() { firstPlayer->player->setDirection({firstPlayer->player->getDirection().x,  1.f}); });
    inputAction->BindAction("A",  [this]() { firstPlayer->player->setDirection({-1.f, firstPlayer->player->getDirection().y}); });
    inputAction->BindAction("D", [this]() { firstPlayer->player->setDirection({1.f,  firstPlayer->player->getDirection().y}); });

    inputAction->BindAction("I",    [this]() { secondPlayer->player->setDirection({secondPlayer->player->getDirection().x, -1.f}); });
    inputAction->BindAction("K",  [this]() { secondPlayer->player->setDirection({secondPlayer->player->getDirection().x,  1.f}); });
    inputAction->BindAction("J",  [this]() { secondPlayer->player->setDirection({-1.f, secondPlayer->player->getDirection().y}); });
    inputAction->BindAction("L", [this]() { secondPlayer->player->setDirection({1.f,  secondPlayer->player->getDirection().y}); });
}

void Game::initializePlayers()
{
    firstPlayer = std::make_shared<AirHockeyPlayer>();
    secondPlayer = std::make_shared<AirHockeyPlayer>();

    firstPlayer->playerColor = sf::Color::Blue;
    secondPlayer->playerColor = sf::Color::Red;
    
    firstPlayer->player = std::make_shared<Mallet>(30);
    secondPlayer->player = std::make_shared<Mallet>(30);

    firstPlayer->player->initialize(firstPlayer->playerColor, true, window->getSize().x, window->getSize().y);
    secondPlayer->player->initialize(secondPlayer->playerColor, false, window->getSize().x, window->getSize().y);

    firstPlayer->mallet = firstPlayer->player->malletShape;
    secondPlayer->mallet = secondPlayer->player->malletShape;
}

void Game::movePuck()
{
    hockeyPuck->move(window->getSize().x, window->getSize().y);
}