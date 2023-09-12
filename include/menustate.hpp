#pragma once

#include <vector>
#include "state.hpp"
#include "menuplaydata.hpp"

class MenuState : public State {
public:
    MenuState(MenuPlayData&);
    State::Type Update() override;
    void HandleEvents(sf::RenderWindow&, sf::Event&) override;
    void Render(sf::RenderWindow&) override;
    State::Type GetType() const override;

private:
    MenuPlayData& menuPlayData_;
    std::vector<std::string> loadedSongs;
    void loadSongs();
};