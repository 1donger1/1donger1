#ifndef _SERVER_H_
#define _SERVER_H_
 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/epoll.h>
#include "threadpool.h"
#include <sqlite3.h>

#define PORT 9999

typedef struct userinfo
{
    int cfd;         //用户的通信套接字
    char name[32];   //用户姓名
    char id[32];     //用户账号
    char passwd[32]; //用户密码
    int cmd;         //用户请求
    char toname[32]; //聊天对象
    char msg[1024];    //聊天内容
    int isSlience;    //是否被禁言
    char buf[204800];    //传输的文件
}userinfo;

typedef struct Onlineuser //在线用户链表
{
    char name[32];
    char account[32]; //账号
    int cfd;          //通信描述符
    int admflag;      //管理员标志
    int slienceflag;  //禁言标志
    struct Onlineuser *next;
}Onlineuser;

void * readevent(void *arg);

void set_noblock(int cfd); //设置非阻塞

int tcp_server_create();//服务器创建

int read_noblock(int cfd,userinfo *user,size_t size); //非阻塞的读

int read_block(int cfd,userinfo *user,size_t size); //阻塞的读

void Regist(userinfo *user); //用户注册

void Login(userinfo *user);//用户登录

sqlite3 *Create_Sqlite(void);  //创建数据库

int Save_User(userinfo *user, sqlite3 *datebase);//注册时保存用户账号和密码

int callback(void *data, int argc, char **argv, char **azColName); //数据库执行语句回调函数

void Chat_One(userinfo* user); //私聊

void Chat_All(userinfo* user); //群聊

void DeleteNode(Onlineuser *user, int cfd);

void Search_Online_User(userinfo *user);

void Adm_Request(userinfo *user);

void Agree_Request(userinfo *user);

void Log_Off(userinfo *user);  //踢用户下线

void Slience_User(userinfo *user); //禁言

void Unban_User(userinfo *user); //解禁

void Send_File(userinfo *user); //发送文件

#endif