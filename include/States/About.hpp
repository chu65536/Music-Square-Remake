#pragma once

#include "States/State.hpp"


class About : public State {
public:
    About() = default;
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    bool m_exit = false;
};