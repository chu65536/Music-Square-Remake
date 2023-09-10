#pragma once

#include <SFML/Graphics.hpp>

class State {
public:
    virtual State* handleEvent(const sf::Event&) = 0;
    virtual void update(sf::Time) = 0;
    virtual void render(sf::RenderWindow&) = 0;
    virtual ~State() = default; 
};