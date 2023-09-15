#pragma once

#include <SFML/Audio.hpp>


class Conductor {
public:
    Conductor(sf::Music& music);
    void Play();
    void Pause();
    void Stop();
    float GetPlaybackPosition() const;
    sf::SoundSource::Status GetStatus() const;

private:
    sf::Music& music_;
};