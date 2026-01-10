#include <muduo/base/Logging.h>
#include "usrmodel.hpp"
#include "db.hpp"
#include <iostream>

using namespace std;

bool UserModel::insert(User &user)
{
    // 组织sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name,password,state) values('%s', '%s','%s')",
            user.getName().c_str(), user.getPasswd().c_str(), user.getState().c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // LOG_INFO << "add User success => sql:" << sql;
            // 获取成功注册的用户id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    LOG_INFO << "add User error => sql:" << sql;
    return false;
}