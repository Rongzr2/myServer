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

User UserModel::query(int id)
{
    // 组织sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPasswd(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);
                return user;
            }
        }
    }
    LOG_INFO << "query User error => sql:" << sql;
    return User();
}

bool UserModel::updateState(User user)
{
    // 组织sql语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state='%s' where id=%d", user.getState().c_str(), user.getId());
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    LOG_INFO << "updateState error => sql:" << sql;
    return false;
}

// ctl+c导致用户重置
void UserModel::resetState()
{
    // 组织sql语句
    char sql[1024] = "update user set state='offline' where state='online'";
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}