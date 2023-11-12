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
    void Move(float value);
private:
    sf::Music& m_music;
    float m_normalizeValue = 0.1f;
};