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
    void Normalize(float& time);
private:
    sf::Music& music_;
    float normalizeValue_ = 0.1f;
};