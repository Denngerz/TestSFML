#pragma once
#include <SFML/Graphics.hpp>
#include "../Core/GameLoop.h"

class Mallet;
class Puck;
class InputAction;

struct AirHockeyPlayer
{
    AirHockeyPlayer(int radius, sf::Color color, bool isOnLeft, int windowX, int windowY);
    
    std::shared_ptr<Mallet> playersMallet;

    sf::Color malletColor;

    std::shared_ptr<InputAction> inputAction;

    int scoredGoals = 0;

    bool didPlayerWon();
};

class Game:GameLoop
{
public:
    Game();
    
    void generate();

    void runLoop();

    void logic();

    void getInput();

    bool isEndGame();

    void draw();
  
private:
    static constexpr int windowWidth = 800;
    
    static constexpr int windowHeight = 600;
    
    static constexpr const char* windowTitle = "AirHockey";
    
    static constexpr sf::Color windowBackgroundColor = sf::Color::Green;
    
    void generatePlayers();

    void generatePuck();

    void sendEventToInputActions();

    void movePuck();

    std::shared_ptr<AirHockeyPlayer> firstPlayer;

    std::shared_ptr<AirHockeyPlayer> secondPlayer;

    std::shared_ptr<Puck> puck;

    bool somePlayerWon();

    sf::Event currentEvent;
};
