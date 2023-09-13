#include <filesystem>
#include "conductor.hpp"


Conductor::Conductor(sf::Music& music) :
    music_(music) {}

void Conductor::Play() {
    if (music_.getStatus() != sf::SoundSource::Playing) {
        music_.play();
    }
}

void Conductor::Pause() {
    music_.pause();
}

void Conductor::Stop() {
    music_.stop();
}

float Conductor::GetPlaybackPosition() const {
    return music_.getPlayingOffset().asSeconds();
}

sf::SoundSource::Status Conductor::GetStatus() const {
    return music_.getStatus();
}