#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct sockaddr_in serveraddr;
    socklen_t addrlen = sizeof(serveraddr);

    // 第一步：创建套接字
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("fail to socket");
        exit(1);
    }

    // 第二步：填充服务器网络信息结构体
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    // 第三步：将套接字与服务器网络信息绑定
    if (bind(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0)
    {
        perror("fail to bind");
        exit(1);
    }

    while (1)
    {
        // 第四步：进行通信
        char text[32] = "";
        struct sockaddr_in clientaddr;
        if (recvfrom(sockfd, text, sizeof(text), 0, (struct sockaddr *)&clientaddr, &addrlen) < 0)
        {
            perror("fail to recvfrom");
            exit(1);
        }

        printf("[%s - %d]: %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), text);

        strcat(text, "*o*");

        if (sendto(sockfd, text, sizeof(text), 0, (struct sockaddr *)&clientaddr, addrlen) < 0)
        {
            perror("fail to sendto");
            exit(1);
        }
    }

    close(sockfd);

    return 0;
}