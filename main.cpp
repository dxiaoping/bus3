#include <iostream>
#include "bus.h"
//#include "bus_station.h"


int main() {
    user *loginUser;
    userInfo *users;
    //��ʼ�����Ա�
    users=users_init(users);
    //��õ�¼���û��ṹ��
    loginUser = login_menu(users);
    if (loginUser == NULL) return 0;
    user_menu(users,loginUser);
}