#include <iostream>
#include "bus.h"
//#include "bus_station.h"


int main() {
    user *loginUser;
    userInfo *users;
    //初始化线性表
    users=users_init(users);
    //获得登录的用户结构体
    loginUser = login_menu(users);
    if (loginUser == NULL) return 0;
    user_menu(users,loginUser);
}