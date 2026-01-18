#include "friendmodel.hpp"
#include "db.hpp"
#include <muduo/base/Logging.h>

void FriendModel::insert(int userid, int friendid)
{
    char sql[1024] = {0};
    sprintf(sql, "insert ignore into friend(userid, friendid) values('%d', '%d')", userid, friendid);
    MySQL mysql;
    if (mysql.connect())
    {
        bool ret = mysql.update(sql);
        if (ret) {
            LOG_INFO << "add friend success => sql:" << sql;
        } else {
            LOG_INFO << "add friend failed => sql:" << sql;
        }
    }
    else
    {
        LOG_INFO << "connect mysql failed";
    }
}

vector<User> FriendModel::query(int userid)
{
    // 组织sql语句
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid=a.id where b.friendid=%d", userid);

    MySQL mysql;
    vector<User> vecUser;
    if (mysql.connect())
    {
        // 可能有多条离线消息, 需要将结果保存到一个vector中, 返回
        MYSQL_RES *res = mysql.query(sql);
        if (res)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))!=nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vecUser.push_back(user);
            }
            mysql_free_result(res);
            return vecUser;
        }
    }
    LOG_INFO << "query OfflineMessage error => sql:" << sql;
    return vecUser;
}
