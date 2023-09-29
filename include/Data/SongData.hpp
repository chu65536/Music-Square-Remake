#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include "MidiFile.h"


struct SongData {
    std::string chosenSongName;
    sf::Music music;
    smf::MidiFile midi;
    std::vector<double> delays;
    std::vector<unsigned int> notes;
};