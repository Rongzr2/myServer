#ifndef OFFLINEMSGMODEL_HPP
#define OFFLINEMESSAGEMODEL_HPP

#include <string>
#include <vector>
using namespace std;

class OfflineMsgModel
{
public:
    // 存储用户的离线消息
    void insert(int userid, string msg);
    // 读取用户的离线消息
    vector<string> query(int userid);
    // 删除用户的离线消息
    void remove(int userid);
};

#endif