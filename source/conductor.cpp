#include <filesystem>
#include "conductor.hpp"


Conductor::Conductor(const std::string& song) :
    currentSong_(song) {
    readMidi();
    readSong();
}

std::string Conductor::findFileByExtension(const std::string& path, const std::string& ext) const {
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ext) {
            return entry.path();
        }
    }

    std::cout << path << ": file with extension " << ext << " is not found" << std::endl;
    return "";
}

void Conductor::readMidi() {
    std::string songPath = "../resources/songs/" + currentSong_;
    std::string filePath = findFileByExtension(songPath, ".mid");
    if (filePath != "") {
        midiFile_.read(filePath);
    }
}

void Conductor::readSong() {
    std::string songPath = "../resources/songs/" + currentSong_;
    std::string filePath = findFileByExtension(songPath, ".ogg");
    if (filePath != "") {
        music_.openFromFile(filePath);
    }
}

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