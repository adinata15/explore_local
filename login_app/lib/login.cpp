#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <sstream>
#include "../utils/file.hpp"
#include "login.hpp"

Login::Login(std::string userpath)
{
    this->userpath = userpath;
    loadUsers();
    std::cout << "User data has been loaded\n";
}

Login::~Login()
{
    saveUsers();
    // user_record.close();
}

// load users data from local csv file
void Login::loadUsers()
{
    user_data = Utils::read_csv(userpath);
}

// login user (will return false if user not registered)
bool Login::login(std::string user, std::string password)
{
    if (!verify_user(user, password))
        return false;

    std::cout << "User " << user << " has been logged in!\n";
    return true;
}

void Login::saveUsers()
{
    Utils::save_csv(userpath, user_data);
}

bool Login::verify_user(std::string user, std::string password)
{
    if (user_data.find(user) == user_data.end() || password != user_data[user])
        return false;
    return true;
}

bool Login::user_exist(std::string user)
{
    if (user_data.find(user) == user_data.end())
        return false;
    return true;
}

bool Login::change_pass(std::string user, std::string new_pass)
{
    user_data[user] = new_pass;
    return true;
}

bool Login::add_user(std::string user, std::string password)
{
    if (user_data.find(user) != user_data.end())
        return false;
    user_data[user] = password;
    return true;
}