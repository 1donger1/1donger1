#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define N 128
#define ERR_LOG(errmsg) \
    do                  \
    {                   \
        perror(errmsg); \
        exit(1);        \
    } while (0)

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage:%s [server_ip] [server_port]\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct sockaddr_in serveraddr;

    // 第一步：创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        ERR_LOG("fail to socket");
    }

    // 第二步：填充服务器网络信息结构体
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    // 第三步：发送客户端连接请求
    /**
     * int connect(int __fd, const struct sockaddr *__addr, socklen_t __len)
     * fd:文件描述符，socket函数的返回值
     * addr:要连接的网络服务器的网络信息载体（需要自己设置）
     * len:addr的长度
     */
    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        ERR_LOG("fail to connect");
    }

    // 第四步：进行通信
    char buf[N] = "";
    while (1)
    {
        fgets(buf, N, stdin);
        buf[strlen(buf) - 1] = '\0';

        /**
         * ssize_t send(int __fd, const void *__buf, size_t __n, int __flags)
         * fd:文件描述符
         * buf:发送的数据
         * n:buf的长度
         * flag:标志位————0代表阻塞、MSG_DONTWAIT表示非阻塞
         */
        if (send(sockfd, buf, N, 0) < 0)
        {
            ERR_LOG("fail to send");
        }

        if (strncmp(buf, "quit", 4) == 0)
        {
            exit(0);
        }

        /**
         * ssize_t recv(int __fd, void *__buf, size_t __n, int __flags)
         * fd:文件描述符--客户端用sockfd,服务器用acceptfd
         * buf:保存接收到的数据
         * n:buf的长度
         * flag:标志位————0代表阻塞、MSG_DONTWAIT表示非阻塞
         */
        if (recv(sockfd, buf, N, 0) < 0)
        {
            ERR_LOG("fail to recv");
        }

        printf("from server: %s\n", buf);
    }

    //第四步：关闭套接字
    close(sockfd);

    return 0;
}