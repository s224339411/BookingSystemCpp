#ifndef USER_H
#define USER_H

#include <string>
using std::string;

struct user{
    string name;
    string password;

    //Constructors
    user(string name,string password);
    user();

    void print_user();
};

#endif // USER_H
