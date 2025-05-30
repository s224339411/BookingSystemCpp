#include "user.h"
#include <iostream>
#include <QDebug>

user::user(string name,string password): name(name),password(password) {}

user::user(): name(""),password("") { }

void user::print_user(){
    qDebug() << "User: " << name << ", Password: " << password;
}
