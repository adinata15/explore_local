#include <iostream>
#include <string>
#include "headers/login.hpp"
#include "headers/database.hpp"
/*
Main idea:
- Database of user password is stored in local computer
- Data is loaded to memory on program start up
- For first login, need to user existing user and corresponding password
- After login, user can register other user (but the username need to be unique)
- Upon registration, new user entry will be able to be used
- This update is only on local computer and is not sync to the database yet as all data here are only processed on local memory
- Only when program is stopped then the database entry will be updated
*/
int main()
{
    std::string curr_user, password, filepath, userpath, name;
    userpath = "database/user.csv";
    Login login(userpath);
    do
    {
        std::cout << "Input name: ";
        std::cin >> curr_user;
        std::cout << "Input password: ";
        std::cin >> password;

        if (login.login(curr_user, password))
            break;

        std::cout << "Wrong username or password. Please input correct details :)\n";
    } while (true);

    // std::cout << "Input filepath name: ";
    // std::cin >> filepath;
    filepath = "database/data.txt"; // hardcoded for simplicity of testing
    Database database(filepath);
    bool is_exit = false;
    do
    {
        int choice = 3; // default to exit program
        std::cout << "What do you want to do?\n";
        std::cout << "0. Add user\n1. Change password\n2. Input data to database\n3. Exit program\n";
        std::cin >> choice;
        std::string input;
        switch (choice)
        {
        case 0:
            std::cout << "You have chosen to add new user\n";
            std::cout << "Input the username:\n";
            std::cin >> name;
            std::cout << "Input the password:\n";
            std::cin >> password;
            if (login.add_user(name, password))
                std::cout << "Succesfully add user\n";
            else
                std::cout << "Failed to add user\n";
            break;
        case 1:
            std::cout << "Input your new password\n";
            std::cin >> password;
            if (login.change_pass(curr_user, password))
                std::cout << "Succesfully changed password\n";
            else
                std::cout << "Failed to change  password\n";
            break;
        case 2:
            std::cout << "Input new data for the database\n";
            std::cin >> input;
            database.editData(input);
            break;
        case 3:
            is_exit = true;
            break;

        default:
            std::cout << "Your command is not understood. Please input again.\n";
            break;
        }
    } while (!is_exit);
    std::cout << "Thank you and see you again\n";
    return 0;
}