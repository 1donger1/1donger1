#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>

// UDP套接字的创建
int main()
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("fail to socket");
        exit(1);
    }

    printf("sockfd = %d\n", sockfd);

    return 0;
}

#include <netinet/in.h>

// 在网络编程中经常使用的结构体---sockaddr_in
struct in_addr
{
    in_addr_t s_addr; // ip地址 4字节
};

struct sockaddr_in
{
    sa_family_t sin_family;  // 协议族 2字节
    in_port_t sin_port;      // 端口号 2字节
    struct in_addr sin_addr; // ip地址 4字节
    char sin_zero[8];        // 填充，不起什么作用， 8字节
};

// 通用结构体----sockaddr
struct sockaddr
{
    sa_family_t sa_family; // 字节
    char sa_data[14];      // 14字节
};

// 为了使不同函数地址能被传入套接字函数，地址需要强制转换为通用套接字地址结构
// 原因是因为不同场合所使用的结构体不一样，但是调入的函数却是同一个，
//所以定义一个通用结构体，当在指定场合使用时，再根据需要传入指定的结构体即可

//两种结构体的使用场合
//在定义源地址和目的地址结构的时候，选用struct sockaddr_in
//当调用编程接口函数，且该函数需要传入地址结构时需要用struct sockaddr进行强制转换