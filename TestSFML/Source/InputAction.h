#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <functional>

class InputAction
{
public:
    void BindKey(sf::Keyboard::Key key, const std::string& actionName);
    
    void BindAction(const std::string& actionName, std::function<void()> actionCallback);
    
    void HandleEvent(const sf::Event& event);
    
private:
    std::map<sf::Keyboard::Key, std::string> keyToAction;
    
    std::map<std::string, std::function<void()>> actionCallbacks;
};