#include "Data/GameData.hpp"


void GameData::Clear() {
    songData.music.stop();
    songData.delays.clear();
    songData.notes.clear();
    map.Clear();
    sf::View defaultView(sf::Vector2f(0.f, 0.f), sf::Vector2f(windowPt->getSize()) / 2.f);
    defaultView.setCenter(-75.f, 0.f);
    windowPt->setView(defaultView);
}