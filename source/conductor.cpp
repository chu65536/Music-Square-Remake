#include "conductor.hpp"
#include <filesystem>

Conductor::Conductor() = default;

void Conductor::Init(const std::string& song) {
    readMidi(song);
    readSong(song);
    status = sf::SoundSource::Stopped;
}

void Conductor::readMidi(const std::string& song) {
    std::string path = "../resources/songs/" + song;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".mid") {
            midiFile.read(entry.path());
            return;
        }
    }

    std::cout << "Error: midi file not found" << std::endl;
}

void Conductor::readSong(const std::string& song) {
    std::string path = "../resources/songs/" + song;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".ogg") {
            music.openFromFile(entry.path());
            return;
        }
    }

    std::cout << "Error: ogg file not found" << std::endl;
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