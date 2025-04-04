#include "Game.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Time.h"
#include "Player.h"

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
    processPlayerInput(*firstPlayer);
    
    processPlayerInput(*secondPlayer);
}

void Game::logic()
{
    Time::update();
        
    movePuck();

    tryMovePlayers();

    tryHandleHit();

    tryHandleGoal();

    tryRestartRound();
}

void Game::draw()
{
    window->clear(sf::Color::Green);

    gameWindow->drawLines();
    
    window->draw(*hockeyPuck->ball);
    window->draw(*firstPlayer->mallet);
    window->draw(*secondPlayer->mallet);
    
    window->display();
}

void Game::handleHit(AirHockeyPlayer& player)
{
    hockeyPuck->implementHit(player.mallet->getPosition(), player.player->velocity, player.player->mass);
}

bool Game::isPlayerTouchingPuck(AirHockeyPlayer& player)
{
    return hockeyPuck->isTouching(player.mallet->getPosition(), player.mallet->getRadius());
}

void Game::tryHandleHit()
{
    if(isPlayerTouchingPuck(*firstPlayer))
    {
        if(!firstPlayer->didHitPuck)
        {
            handleHit(*firstPlayer);
            firstPlayer->didHitPuck = true;
            return;
        }
    }
    else
    {
        firstPlayer->didHitPuck = false;
    }
    
    if(isPlayerTouchingPuck(*secondPlayer))
    {
        if(!secondPlayer->didHitPuck)
        {
            handleHit(*secondPlayer);
            secondPlayer->didHitPuck = true;
        }
    }
    else
    {
        secondPlayer->didHitPuck = false;
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
    return gameWindow->doesPuckTouchLeftGoal(hockeyPuck->ball->getPosition());
}

bool Game::didPuckTouchRightGoal()
{
    return gameWindow->doesPuckTouchRightGoal(hockeyPuck->ball->getPosition());
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

void Game::generateHockeyPuck()
{
    hockeyPuck = new Ball(20);

    hockeyPuck->initialize(window->getSize().x, window->getSize().y);
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
    firstPlayer->keyBindings = {
        {sf::Keyboard::Key::W, sf::Vector2f(0.0f, -1.0f)},
        {sf::Keyboard::Key::S, sf::Vector2f(0.0f, 1.0f)},
        {sf::Keyboard::Key::A, sf::Vector2f(-1.0f, 0.0f)},
        {sf::Keyboard::Key::D, sf::Vector2f(1.0f, 0.0f)}
    };

    secondPlayer->keyBindings = {
        {sf::Keyboard::Key::I, sf::Vector2f(0.0f, -1.0f)},
        {sf::Keyboard::Key::K, sf::Vector2f(0.0f, 1.0f)},
        {sf::Keyboard::Key::J, sf::Vector2f(-1.0f, 0.0f)},
        {sf::Keyboard::Key::L, sf::Vector2f(1.0f, 0.0f)}
    };
}

void Game::initializePlayers()
{
    firstPlayer = std::make_shared<AirHockeyPlayer>();
    secondPlayer = std::make_shared<AirHockeyPlayer>();
    
    firstPlayer->player = std::make_shared<Player>(30);
    secondPlayer->player = std::make_shared<Player>(30);

    firstPlayer->player->initialize(firstPlayerColor, window->getSize().x, window->getSize().y, true);
    secondPlayer->player->initialize(secondPlayerColor, window->getSize().x, window->getSize().y, false);

    firstPlayer->mallet = firstPlayer->player->mallet;
    secondPlayer->mallet = secondPlayer->player->mallet;
}

void Game::processPlayerInput(AirHockeyPlayer& player)
{
    player.currentMalletDirrection = sf::Vector2f(0.0f, 0.0f);
    
    auto updateVelocity = [&player](const auto& pair)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            player.currentMalletDirrection = pair.second;
            player.moved = true;
        }
    };

    for (const auto& binding : player.keyBindings)
    {
        updateVelocity(binding);
    }
}

void Game::tryMovePlayer(AirHockeyPlayer& player)
{
    if(player.moved)
    {
        player.player->direction = player.currentMalletDirrection;
        
        player.player->move(window->getSize().x, window->getSize().y);
        
        player.moved = false;

        return;
    }

    player.player->resetVelocity();
}

void Game::tryMovePlayers()
{
    tryMovePlayer(*firstPlayer);
    
    tryMovePlayer(*secondPlayer);
}

void Game::movePuck()
{
    hockeyPuck->move(window->getSize().x, window->getSize().y);
}