#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <sstream>
#include "database.hpp"
#include "../utils/file.hpp"

Database::Database(std::string filepath)
{
    datapath = filepath;
    // std::fstream(filepath, std::ios::in | std::ios::out);
    getData();
    std::cout << "Data from database has been loaded\n";
}

Database::~Database()
{
    saveData();
    // file.close();
}

void Database::editData(std::string input_str)
{
    data = input_str;
    std::cout << "Database data will take effect after system reset\n";
}

// Load data from local file to unordered_map
void Database::getData()
{
    data = Utils::read_txt(datapath);
    std::cout << data << std::endl;
}

void Database::saveData()
{
    // std::cout << "Data:\n"
    //   << data;

    // file.clear();
    // file.seekg(0, std::ios::beg);

    Utils::save_txt(datapath, data);
    std::cout << Utils::read_txt(datapath) << std::endl;
}