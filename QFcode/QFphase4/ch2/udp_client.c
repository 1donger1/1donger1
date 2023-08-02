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
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("fail to socket");
        exit(1);
    }

    // 第二步：填充服务器网络信息结构体
    // inet_addr:将点分十进制字符串Ip地址转化为整形数据
    // htons:将主机字节序转化为网络字节序
    // atoi:将数字型字符串转化整型数据
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi((argv[2])));

    // 第三步：进行通信
    char buf[32] = "";
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';

        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
        {
            perror("fail to sendto");
            exit(1);
        }

        char text[32] = "";
        if (recvfrom(sockfd, text, sizeof(text), 0, (struct sockaddr *)&serveraddr, &addrlen) < 0)
        {
            perror("fail to recvfrom");
            exit(1);
        }

        printf("from server:%s\n", text);

    }
    
    close(sockfd);

    return 0;
}