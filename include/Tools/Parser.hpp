#pragma once

#include "Data/GameData.hpp"
#include "Data/ParsedMapData.hpp"


namespace Parser 
{
void ParseMidi(SongData& data);
ParsedMapData ParseMap(const std::string& path);
Platform::Data ParsePlatform(const std::string& line);
sf::Vector2f ParseVec2(const std::string& line);
}