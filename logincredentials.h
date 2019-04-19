#ifndef LOGINCREDENTIALS_H
#define LOGINCREDENTIALS_H
#include <string>
#include <iostream>

class LoginCredentials
{
public:
    LoginCredentials(std::string user, std::string pass): username(user), password(pass){}
    std::string username;
    std::string password;
};

#endif // LOGINCREDENTIALS_H
