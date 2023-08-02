#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <sys/types.h> //bind、socket、accept函数
#include <sys/socket.h> //listen、memset函数
#include <string.h>
#include <arpa/inet.h> //htonl htons 函数
#include <stdio.h>
#include <sys/stat.h> //文件操作
#include <fcntl.h> //文件操作
#include <unistd.h> //文件操作
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <sqlite3.h>

#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define SYMBOL_DOUBLE_LINE_H "═"
#define SYMBOL_DOUBLE_LINE_V "║"
#define SYMBOL_DOUBLE_CORNER_TOP_LEFT "╔"
#define SYMBOL_DOUBLE_CORNER_TOP_RIGHT "╗"
#define SYMBOL_DOUBLE_CORNER_BOTTOM_LEFT "╚"
#define SYMBOL_DOUBLE_CORNER_BOTTOM_RIGHT "╝"

#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_CYAN "\033[36m"
#define SYMBOL_CORNER_TOP_LEFT "╔"
#define SYMBOL_CORNER_TOP_RIGHT "╗"
#define SYMBOL_CORNER_BOTTOM_LEFT "╚"
#define SYMBOL_CORNER_BOTTOM_RIGHT "╝"
#define SYMBOL_LINE_H "═"
#define SYMBOL_LINE_V "║"


#define PORT 9999
typedef struct userinfo
{
    int cfd;           //用户的通信套接字
    char name[32];     //用户姓名
    char id[32];       //用户账号
    char passwd[32];   //用户密码
    int cmd;           //用户请求
    char toname[32];   //聊天对象
    char msg[1024];    //聊天内容
    int isSlience;     //是否被禁言
    char buf[204800];    //传输的文件
}userinfo;

//pthread_mutex_t mutex;


void *readMsg(void *arg);

int Connect_Server(void);

void print_menu(const char* title, const char* options[], int num_options);

int Ask_server(int client_socket); //服务器访问

void main_menu(); //主界面

void regist(int client_socket); //注册

void login(int client_socket);  //登录

void hide_passwd(char *passwd);//隐藏密码

void user_login(int client_socket); //普通用户登录

void adm_login(int client_socket); //管理员登录

void adm_menu(); //管理员界面

void user_menu(); //普通用户界面

void chat_one(int client_socket);//私聊

sqlite3 * Create_user_sqlite(userinfo *user);//创建数据库用于保存聊天记录

void save_Chat(userinfo *user); //保存聊天记录

void chat_all(int client_socket);//群聊

void search_online_user(int client_socket); //查看在线用户

void adm_request(int client_socket);  //申请成为管理员
 
void logoff_user(int client_socket);  //踢出在线用户

void slience_user(int client_socket); //禁言

void unban_user(int client_socket); //解禁

void search_chat();  //查看聊天记录

void send_file(int client_socket); //发送文件

void revc_require();

void revc_flie(userinfo *user); //接收文件


#endif