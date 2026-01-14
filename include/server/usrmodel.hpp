#ifndef USERMODEL_HPP
#define USERMODEL_HPP

#include "user.hpp"

class UserModel {
public:
    // 添加新用户
    bool insert(User &user);
    
    // 查询
    User query(int id);

    // 更新用户登录状态
    bool updateState(User user);

    // ctl+c导致用户重置
    void resetState();
};

#endif