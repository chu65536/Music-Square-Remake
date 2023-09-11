#pragma once

#include <SFML/Graphics.hpp>

class State {
public:
    enum class Type { Menu, Play };
    virtual State::Type update() = 0;
    virtual void render(sf::RenderWindow&) = 0;
    virtual State::Type getType() const = 0;
    virtual ~State() = default; 
};