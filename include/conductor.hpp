#pragma once

#include <SFML/Audio.hpp>
#include "MidiFile.h"


class Conductor {
public:
    Conductor();
    void Init(const std::string&);
    void Play();
    void Pause();
    void Stop();
    float GetPlaybackPosition() const;
    sf::SoundSource::Status GetStatus() const;

private:
    void readMidi(const std::string&);
    void readSong(const std::string&);
    smf::MidiFile midiFile;
    sf::Music music;
    sf::SoundSource::Status status;
    static std::string currentSong;
};