#pragma once

#include <SFML/Audio.hpp>
#include "MidiFile.h"


class Conductor {
public:
    Conductor(const std::string& song);
    void Play();
    void Pause();
    void Stop();
    float GetPlaybackPosition() const;
    sf::SoundSource::Status GetStatus() const;

private:
    std::string findFileByExtension(const std::string& path, const std::string& ext) const;
    void readMidi();
    void readSong();
    smf::MidiFile midiFile_;
    sf::Music music_;
    const std::string& currentSong_;
};