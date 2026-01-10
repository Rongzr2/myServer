#ifndef USER_HPP
#define USER_HPP

#include <string>
using namespace std;

class User
{
public:
    User(int id = -1, string name = "", string password = "", string state = "offline")
    {
        this->id = id;
        this->name = name;
        this->password = password;
        this->state = state;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getPasswd() const { return password; }
    string getState() const { return state; }

    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setPasswd(string pwd) { this->password = pwd; }
    void setState(string state) { this->state = state; }

private:
    int id;
    string name;    
    string password;
    string state;
};

#endif