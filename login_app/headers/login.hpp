#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

class Login
{
    std::string userpath;
    std::unordered_map<std::string, std::string> user_data;

    void loadUsers();
    bool user_exist(std::string user);
    void saveUsers();
    bool verify_user(std::string user, std::string password);

public:
    Login(const std::string userpath);
    ~Login();
    bool login(std::string user, std::string password);
    bool change_pass(std::string user, std::string password);
    bool add_user(std::string user, std::string password);
};