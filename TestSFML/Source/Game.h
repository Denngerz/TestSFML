#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Window;
class Ball;
class Player;

struct AirHockeyPlayer
{
    std::shared_ptr<Player> player;

    sf::Vector2f currentMalletDirrection;

    std::unordered_map<sf::Keyboard::Key, sf::Vector2f> keyBindings;

    std::shared_ptr<sf::CircleShape> mallet;

    sf::Color playerColor;

    bool moved = false;

    bool didHitPuck = false;

    int score = 0;
};

class Game
{
public:
    Game();

    Window* gameWindow;

    std::shared_ptr<sf::RenderWindow> window;
    
    Ball* hockeyPuck;

    std::shared_ptr<AirHockeyPlayer> firstPlayer;

    std::shared_ptr<AirHockeyPlayer> secondPlayer;
    
    void startGame();

    void generate();

    void generateWindow();

    void generateHockeyPuck();

    void generatePlayers();

    void generateTimer();
    
    bool isEndGame();
    
    void generatePlayersBindings();
    
    void initializePlayers();
    
    void processPlayerInput(AirHockeyPlayer& player);
    
    void tryMovePlayer(AirHockeyPlayer& player);

    void tryMovePlayers();
    
    void movePuck();

    void logic();

    void getInput();

    void draw();

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
