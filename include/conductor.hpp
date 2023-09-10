#pragma once

#include <SFML/Audio.hpp>
#include "MidiFile.h"


class Conductor {
public:
    Conductor();
    void Init();
    void Play();
    void Pause();
    void Stop();
    float GetPlaybackPosition() const;
    sf::SoundSource::Status GetStatus() const;

private:
    void readMidi();
    void readSong();
    smf::MidiFile midiFile;
    sf::Music music;
    sf::SoundSource::Status status;
};