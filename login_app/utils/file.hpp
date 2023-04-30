#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

namespace Utils
{
    // load csv file to unordered map
    std::unordered_map<std::string, std::string> read_csv(const std::string &file);
    bool save_txt(const std::string &filepath, const std::string &input);
    std::string read_txt(const std::string &file);
    bool save_csv(const std::string &filepath, const std::unordered_map<std::string, std::string> &data);
}