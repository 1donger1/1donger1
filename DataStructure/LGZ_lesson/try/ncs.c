#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>

#define SERVPORT 5001

#define SUCCESS 0
#define FAILURE -1

struct message
{
    int action; //显示消息类型，如登陆注册等
    char id[20];
    char name[20];
    char password[20];
    char toid[20];
    char text[500];
    char filename[20];
    char fabulous[20];
    char V[20];
    int flag;//显示消息的标识，用于标记消息是否已读、已删除
};

struct online
{
    int c_fd;
    char id[20];
    char V[20];
    int flag;
    struct online *next;
};

extern int flag;
extern struct online *head;

int setup_sql()
{
    sqlite3 *database;

    int ret = sqlite3_open("usr.db", &database);

    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败!\n");
        return FAILURE;
    }

    char *errmsg = NULL;

    // 定义创建视图表的SQL语句
    char *sql = "create table if not exists usr(id text primary key,name text,password text);";
    ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("创建用户视图表失败!:%s\n", errmsg);
        return FAILURE;
    }

    // 定义创建视图表的SQL语句
    char *ql = "create table if not exists usr(id text ,toid text,chat text);";
    ret = sqlite3_exec(database, ql, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("创建聊天视图表失败!:%s\n", errmsg);
        return FAILURE;
    }

    sqlite3_close(database);

    return SUCCESS;
}

void *thread_func(void *arg)
{
    int connfd, n;
}

int flag = 0;

int main()
{
    int ret;
    int i = 0;

    pthread_t a_thread;

    // 声明socket相关的变量
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr; // 服务器和客户端地址结构体
    socklen_t clilen;

    // 数据库链接初始化
    setup_sql();

    // 创建socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        perror("fail to socket\n");
        return -1;
    }

    // 绑定IP和端口号
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVPORT);          // 设置服务器端口号
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY表示所有可用的本地IP

    // 设置socket选项，端口复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定socket到指定地址和端口号
    ret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1)
    {
        perror("fail to bind\n");
        return -1;
    }

    // 监听端口,等待客户端连接
    ret = listen(listenfd, 10);
    if (ret == -1)
    {
        perror("fail to listen\n");
        return -1;
    }

    printf("等待客户端连接...\n");

    // 进入循环等待客户端连接
    while (1)
    {
        clilen = sizeof(cliaddr);

        for (; i < 10; i++)
        {
            connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
            if (connfd == -1)
            {
                perror("fail to accept\n");
                return -1;
            }

            printf("成功接收到一个客户端:%s\n", inet_ntoa(cliaddr.sin_addr));

            // 创建线程处理客户端请求
            if (pthread_create(&a_thread, NULL, thread_func, (void *)&connfd) != 0)
            {
                perror("fail to pthread_create");
                exit(-1);
            }
        }

        // 当客户端已满时退出循环
        if (i == 10)
        {
            printf("客户端满!\n");
            break;
        }
    }

    pthread_detach(a_thread);
    close(listenfd);

    return 0;
}