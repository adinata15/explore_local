#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <sstream>

enum COMMAND_TYPE
{
    NORMAL = 3,
    WITH_OPTIONS = 4,
};

std::vector<std::string> read_txt(const std::string &filepath)
{
    std::vector<std::string> data;
    std::string line;
    std::fstream file = std::fstream(filepath, std::ios::in | std::ios::out);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            data.push_back(line);
        }
    }

    file.close();

    return data;
}

void substitute(std::vector<std::string> &data, const std::string &target, const std::string &replacement, bool is_global)
{
    for (std::string &line : data)
    {
        std::regex r_target(target);
        if (is_global)
            line = std::regex_replace(line, r_target, replacement, std::regex_constants::match_any);
        else
            line = std::regex_replace(line, r_target, replacement, std::regex_constants::format_first_only);
    }
}

// std::vector<std::string> parseCommand(char *argv[])
// {
// }

void execute(int argc, char *argv[], std::vector<std::string> &data)
{
    std::string filename, command, option;
    std::vector<std::string> tokens;
    std::istringstream iss;
    std::string token;

    // interpret input format
    switch (argc)
    {
    case NORMAL:
        // ccsed s/this/that/g filename
        command = argv[1];
        filename = argv[2];
        data = read_txt(filename);
        iss = std::istringstream(command);
        while (std::getline(iss, token, '/'))
        {
            tokens.push_back(token);
            // std::cout << token << std::endl;
        }
        if (tokens[0] == "s")
        {
            substitute(data, tokens[1], tokens[2], tokens.size() > 3 && tokens[3] == "g");
        }
        break;
    default:
        std::cout << "Wrong input format" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::string> data;
    execute(argc, argv, data);
    for (std::string &s : data)
    {
        std::cout << s << std::endl;
    }
    return 0;
}