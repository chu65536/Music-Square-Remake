#include <unordered_map>
#include "MidiFile.h"
#include "Adds/Parser.hpp"
#include "Data/SongData.hpp"
#include "Adds/Debug.hpp"


void Parser::Parse(SongData& data) {
    DEBUG_TIMER_START();
    data.midi.doTimeAnalysis();
    data.midi.linkNotePairs();
    data.midi.joinTracks();

    std::unordered_map<uint, int> mp;
    int num = 1;
    for (size_t event = 0; event < data.midi[0].size(); ++event) {
        if (data.midi[0][event].isNoteOn()) {
            uint note = data.midi[0][event].getKeyNumber();
            if (!mp[note]) {
                mp[note] = num;
                num++;
            }
            double time = data.midi[0][event].seconds;
            if (data.delays.size() == 0) {
                data.delays.emplace_back(time);
                data.notes.emplace_back(mp[note]);
            }
            if (data.delays[data.delays.size() - 1] != time) {
                data.delays.emplace_back(time);
                data.notes.emplace_back(mp[note]);
            }
        }
    }
    DEBUG_TIMER_STOP("Midi parsed");
}