#include "offlinemsgmodel.hpp"
#include "muduo/base/Logging.h"
#include "user.hpp"
#include "db.hpp"

// 存储用户的离线消息
void OfflineMsgModel::insert(int userid, string msg)
{
    long timestamp = time(NULL);
    // 组织sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage(userid, message, createtime) values('%d', '%s', '%ld')", userid, msg.c_str(), timestamp);
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
    LOG_INFO << "add OfflineMessage error => sql:" << sql;
    return;
}

// 读取用户的离线消息
vector<string> OfflineMsgModel::query(int userid)
{
    // 组织sql语句
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid=%d", userid);

    MySQL mysql;
    vector<string> vec;
    if (mysql.connect())
    {
        // 可能有多条离线消息, 需要将结果保存到一个vector中, 返回
        MYSQL_RES *res = mysql.query(sql);
        if (res)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)))
            {
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
            return vec;
        }
    }
    LOG_INFO << "query OfflineMessage error => sql:" << sql;
    return vec;
}

// 删除用户的离线消息
void OfflineMsgModel::remove(int userid)
{
    // 组织sql语句
    char sql[1024] = {0};
    sprintf(sql, "delete offlinemessage where userid=%d", userid);
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
    LOG_INFO << "update OfflineMessage error => sql:" << sql;
    return;
}