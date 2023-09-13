#pragma once

#include "MidiFile.h"


class Parser {
public:
    Parser();
    void Parse(const smf::MidiFile& file);
private:
    smf::MidiFile midiFile_;
};