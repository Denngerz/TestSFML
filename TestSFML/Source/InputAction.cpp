#include "InputAction.h"

void InputAction::BindKey(sf::Keyboard::Key key, const std::string& actionName) {
    keyToAction[key] = actionName;
}

void InputAction::BindAction(const std::string& actionName, std::function<void()> actionCallback) {
    actionCallbacks[actionName] = actionCallback;
}

void InputAction::HandleEvent(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto it = keyToAction.find(event.getIf<sf::Event::KeyPressed>()->code);
        if (it != keyToAction.end()) {
            const std::string& actionName = it->second;
            if (actionCallbacks.count(actionName)) {
                actionCallbacks[actionName]();
            }
        }
    }
}