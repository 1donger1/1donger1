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

    struct sockaddr_in ServerAddr;
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(atoi(argv[2]));
    ServerAddr.sin_addr.s_addr = inet_addr(argv[1]);
    if (connect(sock, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) != 0)
    {
        perror("connect");
        return -1;
    }

    while (1)
    {
        char temp[100] = {0};
        scanf("%[^\n]", temp);
        while (getchar() != '\n')
            ;
        if (send(sock, temp, 100, 0) < 0)
        {
            perror("recv");
        }
        
    }
    
    close(sock);
    return 0;
}
