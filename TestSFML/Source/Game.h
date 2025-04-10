#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "../Core/GameLoop.h"

class Window;
class Puck;
class Mallet;
class InputAction;

struct AirHockeyPlayer
{
    std::shared_ptr<Mallet> player;

    std::shared_ptr<sf::CircleShape> mallet;

    sf::Color playerColor;

    bool moved = false;

    int score = 0;
};

class Game:GameLoop
{
public:
    Game();

    void startGame();
    
    void logic();
    
    void getInput();

    void draw();

private:
    Window* gameWindow;

    std::shared_ptr<InputAction> inputAction;

    std::shared_ptr<sf::RenderWindow> window;
    
    std::shared_ptr<Puck> hockeyPuck;

    std::shared_ptr<AirHockeyPlayer> firstPlayer;

    std::shared_ptr<AirHockeyPlayer> secondPlayer;

    void generate();

    void generateWindow();

    void movePlayers();

    void generateHockeyPuck();

    void generatePlayers();

    void generateTimer();
    
    bool isEndGame();
    
    void generatePlayersBindings();
    
    void initializePlayers();
    
    void movePuck();

    void handleHit(AirHockeyPlayer& player);

    bool isPlayerTouchingPuck(AirHockeyPlayer& player);
    
    void tryHandleHit();

    void handleGoal(AirHockeyPlayer& scoredPlayer);

    void tryHandleGoal();

    void tryRestartRound();
    
    bool didPuckTouchLeftGoal();
    
    bool didPuckTouchRightGoal();

    void restartRound();

    bool shouldRestart = false;
};
