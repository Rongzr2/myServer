#ifndef GROUSER_HPP
#define GROUPUSER_HPP

#include <string>
#include "user.hpp"
using namespace std;

class GroupUser : public User
{
public:
    void setRole(string role) { this->role = role; }
    string getRole() { return this->role; }
private:
    string role;
};

#endif