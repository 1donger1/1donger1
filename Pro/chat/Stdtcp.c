#include <stdio.h>      // 包含标准输入输出库的头文件
#include <stdlib.h>     // 包含标准库的头文件
#include <unistd.h>     // 包含 POSIX 系统调用库的头文件
#include <arpa/inet.h>  // 包含网络库的头文件
#include <sys/socket.h> // 包含套接字库的头文件
#include <netinet/in.h> // 包含互联网库的头文件
#include "Stdtcp.h"     // 包含自定义的 TCP 操作头文件

// 定义服务器结构体
struct TcpServer
{
    int sock; // 服务器套接字
};

// 初始化 TCP 服务器
TcpS *InitTcpServer(const char *ip, short int port)
{
    TcpS *s = (TcpS *)malloc(sizeof(TcpS)); // 为服务器结构体分配内存
    if (s == NULL)
    {
        perror("fail to InitTcpServer malloc\n"); // 如果分配失败，输出错误信息
        return NULL;
    }

    s->sock = socket(AF_INET, SOCK_STREAM, 0); // 创建套接字
    if (s->sock < 0)
    {
        perror("fail to socket\n"); // 如果创建失败，输出错误信息
        free(s);
        return NULL;
    }

    int on = 1;
    if (setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0) // 设置套接字选项
    {
        perror("fail to setsockpot\n"); // 如果设置失败，输出错误信息
        free(s);
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(s->sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) // 绑定套接字
    {
        perror("bind"); // 如果绑定失败，输出错误信息
        free(s);
        return NULL;
    }

    if (listen(s->sock, 10) < 0) // 监听套接字
    {
        perror("fail to listen\n"); // 如果监听失败，输出错误信息
        free(s);
        return NULL;
    }

    return s; // 返回初始化的服务器结构体
}

// 接受客户端连接
int TcpServerAccept(TcpS *s)
{
    struct sockaddr_in addr;
    socklen_t len;
    int acceptSock = 0;
    if ((acceptSock = accept(s->sock, (struct sockaddr *)&addr, &len)) < 0) // 接受客户端连接
    {
        perror("fail to TcpServerAccept accept\n"); // 如果接受失败，输出错误信息
        return -1;
    }
    return acceptSock; // 返回已接受连接的套接字
}

// 服务器发送数据
void TcpServerSend(int ClientSock, void *ptr, size_t size)
{
    if (send(ClientSock, ptr, size, 0) < 0) // 发送数据
    {
        perror("fail to TcpServerSend send\n"); // 如果发送失败，输出错误信息
        return;
    }
}

// 服务器接收数据
void TcpServerRecv(int ClientSock, void *ptr, size_t size)
{
    if (recv(ClientSock, ptr, size, 0) < 0) // 接收数据
    {
        perror("fail to TcpServerRecv recv\n"); // 如果接收失败，输出错误信息
        return;
    }
}

// 清理服务器资源
void ClearTcpServer(TcpS *s)
{
    close(s->sock); // 关闭套接字
    free(s);        // 释放服务器结构体内存
}

/*******************************Client***********************************/

// 定义客户端结构体
struct TcpClient
{
    int sock; // 客户端套接字
};

// 初始化 TCP 客户端
TcpC *InitTcpClient(const char *ServerIp, short int ServerPort)
{
    TcpC *c = (TcpC *)malloc(sizeof(TcpC)); // 为客户端结构体分配内存
    if (c == NULL)
    {
        perror("fail to InitTcpClient malloc\n"); // 如果分配失败，输出错误信息
        return NULL;
    }

    c->sock = socket(AF_INET, SOCK_STREAM, 0); // 创建套接字
    if (c->sock < 0)
    {
        perror("fail to InitTcpClient sock\n"); // 如果创建失败，输出错误信息
        free(c);
        return NULL;
    }

    struct sockaddr_in ServerAddr;
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(ServerPort);
    ServerAddr.sin_addr.s_addr = inet_addr(ServerIp);
    if (connect(c->sock, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) < 0) // 连接服务器
    {
        perror("fail to connet\n"); // 如果连接失败，输出错误信息
        free(c);
        return NULL;
    }
    return c; // 返回初始化的客户端结构体
}

// 客户端发送数据
void TcpClientSend(TcpC *c, void *ptr, size_t size)
{
    if (send(c->sock, ptr, size, 0) < 0) // 发送数据
    {
        perror("fail to TcpClientSend send\n"); // 如果发送失败，输出错误信息
        return;
    }
}

// 客户端接收数据
void TcpClientRecv(TcpC *c, void *ptr, size_t size)
{
    if (recv(c->sock, ptr, size, 0) < 0) // 接收数据
    {
        perror("fail to TcpClientRecv recv\n"); // 如果接收失败，输出错误信息
        return;
    }
}

// 清理客户端资源
void ClearTcpClient(TcpC *c)
{
    close(c->sock); // 关闭套接字
    free(c);        // 释放客户端结构体内存
}
