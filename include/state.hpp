#pragma once

#include <SFML/Graphics.hpp>


class State {
public:
    enum class Type { None, Menu, Play };
    virtual State::Type Update(sf::Time dt) = 0;
    virtual void HandleEvents(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~State() = default; 
};