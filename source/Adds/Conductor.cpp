#include "Adds/Conductor.hpp"


Conductor::Conductor(sf::Music& music) :
    m_music(music) {}

void Conductor::Play() {
    if (m_music.getStatus() != sf::SoundSource::Playing) {
        m_music.play();
    }
}

void Conductor::Pause() {
    m_music.pause();
}

void Conductor::Stop() {
    m_music.stop();
}

float Conductor::GetPlaybackPosition() const {
    return m_music.getPlayingOffset().asSeconds();
}

sf::SoundSource::Status Conductor::GetStatus() const {
    return m_music.getStatus();
}

void Conductor::Normalize(float& timer) {
    float dif = timer - GetPlaybackPosition();
    if (abs(dif) > m_normalizeValue) {
        timer = GetPlaybackPosition();
    }  
}