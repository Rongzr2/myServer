#ifndef PUBLIC_HPP
#define PUBLIC_HPP 

enum MSG_TYPE{
    LOGIN_MSG = 1, // 登录, 调用 登录业务
    LOGIN_MSG_ACK,
    REG_MSG,
    REG_MSG_ACK,    //注册响应
    ONE_CHAT_MSG,
    ADD_FRIEND_MSG, //  添加好友
};

#endif