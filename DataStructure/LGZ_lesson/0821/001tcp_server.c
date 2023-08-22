#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h> //网络传输数据，放结构体地址

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("invaild number!\n");
        return -1;
    }

    // 第一步:创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket:");
        return -1;
    }

    //设置端口复用
    int on = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0)
    {
        perror("setsockpot\n");
        return -1;
    }

    // 第二步:绑定套接字
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2])); // 主机号转网络号
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        perror("bind");
        return -1;
    }

    // 第三步:被动监听
    if (listen(sock, 10) != 0) // 同一时间最大连接数
    {
        perror("listen");
        return -1;
    }

    struct sockaddr_in Clientaddr;
    socklen_t len = sizeof(Clientaddr);
    int acceptSock = 0;
    if ((acceptSock = accept(sock, (struct sockaddr *)&Clientaddr, &len)) < 0)
    {
        perror("accept");
        return -1;
    }

    while (1)
    {
        char temp[100] = {0};
        if (recv(acceptSock, temp, 100, 0) < 0)
        {
            perror("server recv");
        }

        printf("recv :%s\n", temp);
    }

    close(acceptSock);
    close(sock);
    return 0;
}