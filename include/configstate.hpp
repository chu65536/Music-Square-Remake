#pragma once

#include "state.hpp"
#include "configdata.hpp"

class ConfigState : public State {
public:
    ConfigState(ConfigData& data);
    State::Type Update(sf::Time dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void configMenu();
    ConfigData& configData_;
    bool exit_ = false;
};