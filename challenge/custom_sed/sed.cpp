#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <sstream>

std::string read_txt(const std::string &filepath)
{
    std::string data, line;
    std::fstream file = std::fstream(filepath, std::ios::in | std::ios::out);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::cout << line << std::endl;
            data += line;
            data += '\n';
        }
    }

    file.close();

    return data;
}
int main(int argc, char *argv[])
{
    std::string command, filename, data;
    command = argv[1];
    filename = argv[2];

    data = read_txt(filename);
    // std::cout << data << std::endl;
    return 0;
}