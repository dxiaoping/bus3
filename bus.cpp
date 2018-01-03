//
// Created by 平 on 2017/12/31.
//

#include "bus.h"
#include <iostream>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include "bus_station.h"



usersInfo* users_init(usersInfo *users){
    users=(userInfo*)malloc(sizeof(userInfo));
    users->number=0;
    users->users=NULL;
    return users;
}

void registers(usersInfo *users){
    user *user1;
    user1=(user*)malloc(sizeof(user));
    std::cout << "请输入您的账号" << std::endl;
    std::cin >> user1->username;
    user *top =users->users;
    while (top != NULL){
        if(strcmp(top->username,user1->username)==0){
            std::cout << "该用户已经注册，请更换用户名称" <<std::endl;
            return;

        }
        top = top->next;
    }
    std::cout << "请输入您的密码" << std::endl;
    std::cin >> user1->password;
    std::cout << "请输入您的手机号" << std::endl;
    std::cin >> user1->phoneNumber;
    user1->authorty=GUEST;
    user_add(users,user1);
    visit_users(users);
    save_user(users);
}

user *login(usersInfo *users){
    char username[10];
    char password[16];
    user *top;
    while(1){
        bool over_3_time=false;
        if(users->users == NULL)break;
        top=users->users;
        std::cout << "请输入您的账号" << std::endl;
        std::cin >> username;
        while(1){
            if(strcmp(top->username,username)==0){
                int input_count=0;
                while(input_count<3){
                    std::cout << "请输入您的密码" << std::endl;
                    std::cin >> password;
                    if(strcmp(top->password,password)==0)return top;
                    else std::cout << "密码错误" << std::endl;
                    input_count++;
                }
                std::cout << "您已经输错三次密码，请于三小时后重新尝试" << std::endl;
                over_3_time=true;
                break;
            }
            else top=top->next;
            if(top==NULL){
                std::cout << "您输入的账号不存在，请重新输入" << std::endl;
                break;
            }
        }
        if(over_3_time)break;
    }
}

user *login_menu(usersInfo *users){
    int choice;
    user *login_user;
    users=load_user(users);

    while(1){
        bool exit_if =false;
        std::cout <<"欢迎使用城市公交查询系统"<<std::endl;
        std::cout << "1：登录-----------2：注册\n" << std::endl;
        std::cout << "3：退出-----------\n" << std::endl;
        if(std::cin >> choice){
            switch(choice){
                case 1:
                    if(users ->users != NULL){
                        login_user=login(users);
                        return login_user;
                    }
                    else {
                        std::cout << "后台没有任何用，户请先注册" <<std::endl;
                        break;
                    }
                case 2:registers(users);
                    break;
                case 3:
                    return NULL;
            }
        }
    }
} //用户登录，其中包含注册功能；

void user_menu(usersInfo *users,user *loginUser){
    bus_management *bus_management1;
    bus_management1 = load_bus_File();
    while(1){
        std::cout <<"1：修改登录密码-------------2：公交路线查询"<<std::endl;
        std::cout <<"3：修改用户信息-------------4:公交站点查询"<<std::endl;
        std::cout <<"5：站站查询-------------6:最短路径查询"<<std::endl;
        std::cout <<"7：最少换乘查询-------------8:退出登录"<<std::endl;
        std::cout <<"9：注销用户-------------"<<std::endl;
        std::cout <<"10：线路管理"<<std::endl;
        int choice;
        if(std::cin >> choice){
            if(choice > 9 && loginUser->authorty==GUEST){
                std::cout <<"您不是管理员，没有权限使用此功能"<<std::endl;
            }
            else {
                switch(choice){
                    case 1:modify_password(loginUser);
                        break;
                    case 2:search_line(bus_management1);
                        break;
                    case 3:modify_information(loginUser);
                        break;
                    case 4:search_station(bus_management1);
                        break;
                    case 5:search_load(bus_management1);
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:save_user(users);
                        return ;
                    case 9:user_delete(users,loginUser);
                        return;
                    case 10:
                        road_management(bus_management1);
                        break;
                }
            }
        }

    }
}

void modify_information(user *loginUser){
    char password[11];
    int choice;
    int i=0;
    while(i<3){
        bool exit_if=false;
        std::cout << "请输入您的密码" <<std::endl;
        std::cin >> password;
        if(strcmp(loginUser->password,password)==0){
            std::cout <<"请输入您的新手机号" <<std::endl;
            std::cin >>loginUser->phoneNumber;
            std::cout <<"新手机号设置成功" <<std::endl;
            break;
        }
        else {
            std::cout <<"您的身份确认信息有误" <<std::endl;
            i++;
            std::cout <<"您已经输错"<<i<<"次" <<std::endl;
        }
        std::cout <<"1：继续------------2：退出修改"<<std::endl;
        if(std::cin >> choice){
            switch(choice){
                case 1:break;
                case 2:exit_if=true;
            }
        }
        if(exit_if)break;
    }

}

void modify_password(user *loginUser){//修改密码
    char phoneNumber[11];
    int choice;
    int i=0;
    while(i<3){
        bool exit_if=false;
        std::cout << "请输入您的手机号" <<std::endl;
        std::cin >> phoneNumber;
        if(strcmp(loginUser->phoneNumber,phoneNumber)==0){
            std::cout <<"请输入您的新密码" <<std::endl;
            std::cin >>loginUser->password;
            std::cout <<"新密码设置成功" <<std::endl;
            break;
        }
        else {
            std::cout <<"您的身份信息有误" <<std::endl;
            i++;
            std::cout <<"您已经输错"<<i<<"次" <<std::endl;
        }
        std::cout <<"1：继续------------2：退出修改"<<std::endl;
        if(std::cin >> choice){
            switch(choice){
                case 1:break;
                case 2:exit_if=true;
            }
        }
        if(exit_if)break;
    }
}

usersInfo* user_add(usersInfo *users,user *user1){
    if(users->users==NULL){
        users->users=user1;
        users->users->next=NULL;
        users->number++;
    }
    else{
        user1->next=users->users;
        users->users->pre=user1;
        users->users=user1;
        users->number++;
    }
    return users;
}// 增加用户

usersInfo* load_user(usersInfo *users){
    if(!users->users) free(users->users);
    FILE *user_data;
    if(fopen("users_data.txt","r")!=NULL)
    {
        user_data=fopen("users_data.txt","r");
        while (true){
            user *tempUser = (user*)malloc(sizeof(user));
            fread(tempUser, sizeof(user),1,user_data);
            if(feof(user_data)) break;
            user_add(users,tempUser);
        }
        fclose(user_data);
    }
    return users;
}//从文件中读取数据

void user_delete(usersInfo *users,user *user1){
    if(users->number == 1)users->users = NULL;
    else if(user1->next == NULL){
        user1->pre->next = NULL;
    }
    else if(user1->pre == NULL){
        users->users = users->users->next;
        users->users->pre = NULL;
    }
    else if(users->number > 2 ){
        user1->pre->next=user1->next;
        user1->next->pre=user1->pre;
    }
    users->number--;
}//删除用户

void save_user(userInfo *users){
    FILE *user_data=NULL;
    user_data=fopen("users_data.txt","wt");
    user *tempUser = users->users;
    while (tempUser){
        fwrite(tempUser, sizeof(user),1,user_data);
        tempUser = tempUser->next;
    }
    fclose(user_data);
}//保存用户信息

void visit_users(userInfo *userInfo1){
    user *tempUser;
    tempUser = userInfo1->users;
    while (tempUser){
        printf("username:%s\n",tempUser->username);
        tempUser = tempUser->next;
    }
}
