#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

class Database
{
    std::string datapath;
    std::string data;
    void getData();
    void saveData();

public:
    Database(std::string filename);
    ~Database();
    void editData(std::string input_str);
};