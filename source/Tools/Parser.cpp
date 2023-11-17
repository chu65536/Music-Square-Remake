#include <unordered_map>
#include "MidiFile.h"
#include "Tools/Parser.hpp"
#include "Data/SongData.hpp"
#include "Tools/Debug.hpp"
#include <algorithm>


void Parser::Parse(SongData& data) 
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
        }
        if (curTrack.delays.size() != 0)
        {   
            for (auto& delay: curTrack.delays)
            {
                delay -= normalVal;
            }

            curTrack.beginTime = curTrack.delays[0];
            curTrack.endTime = curTrack.delays[curTrack.delays.size() - 1];
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