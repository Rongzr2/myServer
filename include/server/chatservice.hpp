#ifndef CHATSERVICE_HPP
#define CHATSERVICE_HPP 

#include <muduo/net/TcpConnection.h>
#include <functional>
#include <unordered_map>
#include "json.hpp"
#include "usrmodel.hpp"
#include <mutex>
#include "offlinemsgmodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"

using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

// 事件处理的回调函数类型 
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService* instance();

    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 添加好友
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 退出登录
    void logout(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 创建群组
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 加入群组
    void joinGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 获取消息对应的处理方法
    MsgHandler getHandler(int msgid);

    // ctl+c服务器退出后刷新重置用户状态
    void reset();

    // 客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);

private:
    ChatService();

    // 消息 handler, 实现一个消息id对应一个事件处理器
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 用户连接，保存用户连接信息
    std::unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 加锁, 保证_userConnMap的线程安全
    std::mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
    FriendModel _friendModel;
    OfflineMsgModel _offlineMsgModel;
    GroupModel _groupModel;
};

#endif