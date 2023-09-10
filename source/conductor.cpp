#include "conductor.hpp"

Conductor::Conductor() = default;

void Conductor::Init() {
    readMidi();
    readSong();
    status = sf::SoundSource::Stopped;
}

void Conductor::readMidi() {
    if (!midiFile.read("../resources/songs/all star/All Star.mid")) {
        std::cout << "Error: Midi file is not found" << std::endl;
    }
}

void Conductor::readSong() {
    if (!music.openFromFile("../resources/songs/all star/All Star.ogg")) {
        std::cout << "Error: Music file is not found" << std::endl;
    }
}

void Conductor::Play() {
    if (music.getStatus() != sf::SoundSource::Playing) music.play();
    status = sf::SoundSource::Playing;
}

void Conductor::Pause() {
    music.pause();
    status = sf::SoundSource::Paused;
}

void Conductor::Stop() {
    music.stop();
    status = sf::SoundSource::Stopped;
}

float Conductor::GetPlaybackPosition() const {
    return music.getPlayingOffset().asSeconds();
}

sf::SoundSource::Status Conductor::GetStatus() const {
    return status;
}