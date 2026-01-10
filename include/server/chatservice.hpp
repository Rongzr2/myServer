#ifndef CHATSERVICE_HPP
#define CHATSERVICE_HPP 

#include <muduo/net/TcpConnection.h>
#include <functional>
#include <unordered_map>
#include "json.hpp"
#include "usrmodel.hpp"

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

    MsgHandler getHandler(int msgid);

private:
    ChatService();

    // 消息 handler, 实现一个消息id对应一个事件处理器
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 数据操作类对象
    UserModel _userModel;
};

#endif