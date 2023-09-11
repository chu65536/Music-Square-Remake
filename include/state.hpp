#pragma once

#include <SFML/Graphics.hpp>

class State {
public:
    enum class Type { Menu, Play };
    virtual State::Type Update() = 0;
    virtual void HandleEvents(sf::RenderWindow&, sf::Event&) = 0;
    virtual void Render(sf::RenderWindow&) = 0;
    virtual State::Type GetType() const = 0;
    virtual ~State() = default; 
};