#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "file.hpp"

// load csv file to unordered map
std::unordered_map<std::string, std::string> Utils::read_csv(const std::string &filepath)
{
    std::unordered_map<std::string, std::string> data;
    std::string line, word;
    std::fstream file = std::fstream(filepath, std::ios::in | std::ios::out);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::vector<std::string> row;

            std::stringstream str(line);

            while (std::getline(str, word, ','))
                row.push_back(word);

            data[row[0]] = row[1];
        }
    }
    file.close();

    return data;
}

bool Utils::save_csv(const std::string &filepath, const std::unordered_map<std::string, std::string> &data)
{
    std::fstream file = std::fstream(filepath, std::ios::out);

    if (file.is_open())
    {
        for (const auto &user_pass : data)
        {
            file << user_pass.first << "," << user_pass.second << std::endl;
        }
    }
    else
        return false;
    file.close();

    return true;
}

std::string Utils::read_txt(const std::string &filepath)
{
    std::string data, line;
    std::fstream file = std::fstream(filepath, std::ios::in);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            data += line;
            data += '\n';
        }
    }

    file.close();

    return data;
}

// return if write file is successful
bool Utils::save_txt(const std::string &filepath, const std::string &input)
{
    std::string data, line;
    std::fstream file = std::fstream(filepath, std::ios::out); // can use std::ios::app for appending to file

    if (file.is_open())
    {
        file << input << std::endl;
    }
    else
        return false;

    file.close();

    return true;
}