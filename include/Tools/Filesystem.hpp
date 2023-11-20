#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace fs
{
std::vector<std::string> findAllByExt(const std::string& path, const std::string& ext);
}