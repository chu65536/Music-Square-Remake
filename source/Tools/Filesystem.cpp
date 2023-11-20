#include "Tools/Filesystem.hpp"
#include <iostream>

namespace fs
{
std::vector<std::string> findAllByExt(const std::string& path, const std::string& ext)
{   
    std::vector<std::string> res;
    for (const auto& entry: std::filesystem::directory_iterator(path)) 
    {
        if (entry.path().extension() == ext) 
        {
            res.emplace_back(entry.path().string());
        }
    }

    return res;
}
}