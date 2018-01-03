//
// Created by ƽ on 2017/12/31.
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
    std::cout << "�����������˺�" << std::endl;
    std::cin >> user1->username;
    user *top =users->users;
    while (top != NULL){
        if(strcmp(top->username,user1->username)==0){
            std::cout << "���û��Ѿ�ע�ᣬ������û�����" <<std::endl;
            return;

        }
        top = top->next;
    }
    std::cout << "��������������" << std::endl;
    std::cin >> user1->password;
    std::cout << "�����������ֻ���" << std::endl;
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
        std::cout << "�����������˺�" << std::endl;
        std::cin >> username;
        while(1){
            if(strcmp(top->username,username)==0){
                int input_count=0;
                while(input_count<3){
                    std::cout << "��������������" << std::endl;
                    std::cin >> password;
                    if(strcmp(top->password,password)==0)return top;
                    else std::cout << "�������" << std::endl;
                    input_count++;
                }
                std::cout << "���Ѿ�����������룬������Сʱ�����³���" << std::endl;
                over_3_time=true;
                break;
            }
            else top=top->next;
            if(top==NULL){
                std::cout << "��������˺Ų����ڣ�����������" << std::endl;
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
        std::cout <<"��ӭʹ�ó��й�����ѯϵͳ"<<std::endl;
        std::cout << "1����¼-----------2��ע��\n" << std::endl;
        std::cout << "3���˳�-----------\n" << std::endl;
        if(std::cin >> choice){
            switch(choice){
                case 1:
                    if(users ->users != NULL){
                        login_user=login(users);
                        return login_user;
                    }
                    else {
                        std::cout << "��̨û���κ��ã�������ע��" <<std::endl;
                        break;
                    }
                case 2:registers(users);
                    break;
                case 3:
                    return NULL;
            }
        }
    }
} //�û���¼�����а���ע�Ṧ�ܣ�

void user_menu(usersInfo *users,user *loginUser){
    bus_management *bus_management1;
    bus_management1 = load_bus_File();
    while(1){
        std::cout <<"1���޸ĵ�¼����-------------2������·�߲�ѯ"<<std::endl;
        std::cout <<"3���޸��û���Ϣ-------------4:����վ���ѯ"<<std::endl;
        std::cout <<"5��վվ��ѯ-------------6:���·����ѯ"<<std::endl;
        std::cout <<"7�����ٻ��˲�ѯ-------------8:�˳���¼"<<std::endl;
        std::cout <<"9��ע���û�-------------"<<std::endl;
        std::cout <<"10����·����"<<std::endl;
        int choice;
        if(std::cin >> choice){
            if(choice > 9 && loginUser->authorty==GUEST){
                std::cout <<"�����ǹ���Ա��û��Ȩ��ʹ�ô˹���"<<std::endl;
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
        std::cout << "��������������" <<std::endl;
        std::cin >> password;
        if(strcmp(loginUser->password,password)==0){
            std::cout <<"�������������ֻ���" <<std::endl;
            std::cin >>loginUser->phoneNumber;
            std::cout <<"���ֻ������óɹ�" <<std::endl;
            break;
        }
        else {
            std::cout <<"�������ȷ����Ϣ����" <<std::endl;
            i++;
            std::cout <<"���Ѿ����"<<i<<"��" <<std::endl;
        }
        std::cout <<"1������------------2���˳��޸�"<<std::endl;
        if(std::cin >> choice){
            switch(choice){
                case 1:break;
                case 2:exit_if=true;
            }
        }
        if(exit_if)break;
    }

}

void modify_password(user *loginUser){//�޸�����
    char phoneNumber[11];
    int choice;
    int i=0;
    while(i<3){
        bool exit_if=false;
        std::cout << "�����������ֻ���" <<std::endl;
        std::cin >> phoneNumber;
        if(strcmp(loginUser->phoneNumber,phoneNumber)==0){
            std::cout <<"����������������" <<std::endl;
            std::cin >>loginUser->password;
            std::cout <<"���������óɹ�" <<std::endl;
            break;
        }
        else {
            std::cout <<"���������Ϣ����" <<std::endl;
            i++;
            std::cout <<"���Ѿ����"<<i<<"��" <<std::endl;
        }
        std::cout <<"1������------------2���˳��޸�"<<std::endl;
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
}// �����û�

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
}//���ļ��ж�ȡ����

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
}//ɾ���û�

void save_user(userInfo *users){
    FILE *user_data=NULL;
    user_data=fopen("users_data.txt","wt");
    user *tempUser = users->users;
    while (tempUser){
        fwrite(tempUser, sizeof(user),1,user_data);
        tempUser = tempUser->next;
    }
    fclose(user_data);
}//�����û���Ϣ

void visit_users(userInfo *userInfo1){
    user *tempUser;
    tempUser = userInfo1->users;
    while (tempUser){
        printf("username:%s\n",tempUser->username);
        tempUser = tempUser->next;
    }
}
