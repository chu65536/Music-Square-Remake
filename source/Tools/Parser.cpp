#include <unordered_map>
#include "MidiFile.h"
#include "Tools/Parser.hpp"
#include "Data/SongData.hpp"
#include "Tools/Debug.hpp"
#include <algorithm>
#include <sstream>


void Parser::ParseMidi(SongData& data) 
{
    DEBUG_TIMER_START();
    data.midi.doTimeAnalysis();
    data.midi.linkNotePairs();
    //data.midi.joinTracks();

    float normalVal = 1000.0f;
    for (int track = 0; track < data.midi.getTrackCount(); ++track)
    {
        for (size_t event = 0; event < data.midi[track].size(); ++event) 
        {
            if (data.midi[track][event].isNoteOn()) 
            {
                normalVal = std::min(normalVal, (float)data.midi[track][event].seconds);
            }
        } 
    }

    std::map<int, SongData::Track> tracksByID; 
    std::vector<std::pair<float, int>> vec;
    for (int track = 0; track < data.midi.getTrackCount(); ++track)
    {   
        SongData::Track curTrack;
        curTrack.name = "";
        std::unordered_map<unsigned, int> mp;
        int num = 1;
        for (size_t event = 0; event < data.midi[track].size(); ++event) 
        {
            if (data.midi[track][event].isNoteOn()) 
            {
                unsigned note = data.midi[track][event].getKeyNumber();
                if (!mp[note]) 
                {
                    mp[note] = num;
                    num++;
                }
                float time = data.midi[track][event].seconds;
                if (curTrack.delays.empty())
                {
                    curTrack.delays.emplace_back(time);
                    curTrack.notes.emplace_back(mp[note]);  
                } 
                else if (curTrack.delays[curTrack.delays.size() - 1] != time) 
                {
                    curTrack.delays.emplace_back(time);
                    curTrack.notes.emplace_back(mp[note]);
                }
            }
            if (data.midi[track][event].isTrackName())
            {
                curTrack.name = data.midi[track][event].getMetaContent();
            }
        }
        if (curTrack.delays.size() != 0)
        {   
            for (auto& delay: curTrack.delays)
            {
                delay -= normalVal;
            }

            curTrack.beginTime = curTrack.delays[0];
            curTrack.endTime = curTrack.delays[curTrack.delays.size() - 1];
            if (curTrack.name == "")
            {
                curTrack.name = "Unknown instrument " + std::to_string(track + 1);
            }
            tracksByID[track] = curTrack;
            vec.emplace_back(curTrack.beginTime, track);
        }
    }

    sort(vec.begin(), vec.end());
    for (auto p: vec)
    {
       data.tracks.emplace_back(tracksByID[p.second]); 
    }

    DEBUG_TIMER_STOP("Midi parsed");
}

std::vector<float> calcDelays(const std::vector<Platform>& platforms)
{
    std::vector<float> res;
    for (const auto& platform: platforms)
    {
        res.emplace_back(platform.GetTime());
    }

    return res;
}

ParsedMapData Parser::ParseMap(const std::string& path)
{
    ParsedMapData res;

    std::ifstream file(path);
    std::string line;

    enum Mode {none, square_size, track, platforms};
    Mode mode = none;
    ParsedMapData::Track curTrack;
    while(std::getline(file, line))
    {   
        if (line.find("#square_size") != std::string::npos)
        {
            mode = square_size;   
            continue;;
        }
        if (line.find("#track") != std::string::npos)
        {
            mode = track;
        }
        if (line.find("#platforms") != std::string::npos)
        {
            mode = platforms;
            continue;
        }

        switch(mode)
        {
        case track:
            if (curTrack.platforms.size() != 0)
            {   
                std::vector<float> delays = calcDelays(curTrack.platforms);
                curTrack.delays = delays;
                res.tracks.emplace_back(curTrack);
            }
            curTrack.delays.clear();
            curTrack.platforms.clear();
            curTrack.name = line.substr(1, line.size() - 1);
            break;
        case platforms:
        {
            Platform::Data data = ParsePlatform(line);
            data.squareSize = res.squareSize;
            curTrack.platforms.emplace_back(std::move(data));
            break;
        }
        case square_size:
            res.squareSize = ParseVec2(line);
            break;
        }
    }
    std::vector<float> delays = calcDelays(curTrack.platforms);
    curTrack.delays = delays;
    res.tracks.emplace_back(curTrack);

    return res;
}

Platform::Data Parser::ParsePlatform(const std::string& line)
{
    Platform::Data data;
    std::stringstream ss;
    ss.str(line);

    sf::Vector2f pos, sz, spB, spA;
    float time;
    int dir;
    int colR, colG, colB, oColR, oColG, oColB;
    float thick;

    // reading in the same order as written
    ss >> pos.x >> pos.y;
    ss >> sz.x  >> sz.y;
    ss >> dir;
    ss >> time;
    ss >> colR >> colG >> colB;
    ss >> thick;
    ss >> oColR >> oColG >> oColB;
    ss >> spB.x >> spB.y;
    ss >> spA.x >> spA.y; 

    data.position = pos;
    data.time = time;
    data.size = sz;
    data.directions = {static_cast<Platform::Direction>(dir)};
    data.color = sf::Color(colR, colG, colB);
    data.outlineColor = sf::Color(oColR, oColG, oColB);
    data.outlineThickness = thick;
    data.speedBefore = spB;
    data.speedAfter = spA;

    return data;
}

sf::Vector2f Parser::ParseVec2(const std::string& line)
{
    std::stringstream ss;
    ss.str(line);

    float x, y;
    ss >> x >> y;

    return {x, y};
}