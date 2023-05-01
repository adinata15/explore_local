#include <iostream>
#include "utils/file.hpp"
int main()
{
    std::cout << "hi" << std::endl;
    Utils::read_txt("database/data.txt");
    return 0;
}