#pragma once

#include <vector>
#include <string>
#include "MidiFile.h"
#include <SFML/Audio.hpp>

struct SongData 
{
    struct Track
    {   
        std::string name = "";
        std::vector<float> delays;
        std::vector<unsigned int> notes;
        float beginTime;
        float endTime;
    };

    std::string chosenSongName;
    sf::Music music;
    smf::MidiFile midi;
    std::vector<Track> tracks;
};