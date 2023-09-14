#pragma once

#include <vector>
#include "MidiFile.h"


class Parser {
public:
    std::vector<double> Parse(smf::MidiFile& file);
};