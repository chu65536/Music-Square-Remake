#include <set>
#include "MidiFile.h"
#include "Adds/Parser.hpp"


std::vector<double> Parser::Parse(smf::MidiFile& file) {
    file.doTimeAnalysis();
    file.linkNotePairs();

    size_t tracks = file.getTrackCount();
    std::set<double> delays;
    for (size_t track = 0; track < tracks; ++track) {
        for (size_t event = 0; event < file[track].size(); ++event) {
            if (file[track][event].isNoteOn())
                delays.insert(file[track][event].seconds);

        }
    }

    std::vector<double> ret(delays.begin(), delays.end()); 
    return ret;
}