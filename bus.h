//
// Created by ƽ on 2017/12/31.
//

#ifndef BUS_BUS_H
#define BUS_BUS_H

#endif //BUS_BUS_H


#define ROOT 1
#define GUEST 2
#define OK 1
#define FALSE 0


//�û���Ϣ
typedef struct users{
    int authorty;
    char username[10];
    char password[16];
    char phoneNumber[12];
    struct users *next;
    struct users *pre;
} user;

//���Ա����û�
typedef struct userInfo{
    int number;
    struct users *users;
} usersInfo;




usersInfo* users_init(userInfo *users);
void modify_password(user *loginUser);
void modify_information(user *loginUser);
user *login(usersInfo *users);
void registers(usersInfo*users);
user *login_menu(usersInfo *users); //�û���¼�����а���ע�Ṧ�ܣ�
void user_menu(usersInfo *users,user *loginUser);//�û�����;
usersInfo* user_add(usersInfo *users,user *user1);// �����û�
void user_delete(usersInfo *users,user *user1);//ɾ���û�
usersInfo* load_user(usersInfo *users);//���ļ��ж�ȡ����
void save_user(userInfo *users);//�����û���Ϣ
void visit_users(userInfo *userInfo1);
