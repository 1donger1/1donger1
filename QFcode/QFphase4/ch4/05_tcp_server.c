// tcp服务器的实现
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

#define N 128
#define ERR_LOG(errmsg) \
    do                  \
    {                   \
        perror(errmsg); \
        exit(1);        \
    } while (0)

int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "Usage: %s [server_ip] [server_port]\n", argv[0]);
        exit(1);
    }

    int sockfd, acceptfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(serveraddr);

    // 第一步：创建套接字
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        ERR_LOG("fail to socket");
    }

    int on = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        ERR_LOG("fail to setsockopt");
    }

    // 第二步：填充服务器网络信息结构体
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    // 第三步：将套接字与服务器网络信息结构体绑定
    /**
     * int bind(int __fd, const struct sockaddr *__addr, socklen_t __len)
     * 功能：将套接字与网络信息结构体绑定
     * fd:文件描述符
     * addr:网络信息结构体
     * len:addr的长度
     */
    if(bind(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0)
    {
        ERR_LOG("fail to bind");
    }
 
    // 第四步：将套接字设置为监听状态
    /**
     * int listen(int __fd, int __n)
     * 功能：将套接字设置为被动监听状态，做到这样之后就可以接收到连接请求
     * fd:文件描述符
     * n:允许通信链接的主机个数，一般设置5、10
     */
    if(listen(sockfd, 5) < 0)
    {
        ERR_LOG("fail to listen");
    }

    // 第五步：阻塞等待客户端连接请求
    /**
     * int accept(int __fd, struct sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len)
     * 功能：阻塞等待客户端的连接请求
     * fd:文件描述符
     * addr:接收到的客户端的信息结构体(自动填充，定义变量即可)
     * addr_len:addr的长度
     * 返回值：
     * 成功：新的文件描述符(只要有客户端连接，就会产生新的文件描述符
     *      这个新的文件描述符专门与指定的客户端进行通信)
     * 失败:-1
     */
    if((acceptfd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
    {
        ERR_LOG("fail to accept");
    }

    printf("%s--%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

    // 第六步：进行通信
    char buf[N] = "";
    ssize_t bytes;
    while(1)
    {
        /**
         * ssize_t recv(int __fd, void *__buf, size_t __n, int __flags)
         * fd:文件描述符--客户端用sockfd,服务器用acceptfd
         * buf:保存接收到的数据
         * n:buf的长度
         * flag:标志位————0代表阻塞、MSG_DONTWAIT表示非阻塞
         */
        if((bytes = recv(acceptfd, buf, N, 0)) < 0)
        {
            ERR_LOG("fail to recv");
        }
        else if(bytes == 0)
        {
            printf("The client quit\n");
            exit(1);
        }

        if(strncmp(buf, "quit", 4) == 0)
        {
            exit(0);
        }

        printf("from client %s\n", buf);
        strcat(buf, "*o*");

        /**
         * ssize_t send(int __fd, const void *__buf, size_t __n, int __flags)
         * fd:文件描述符
         * buf:发送的数据
         * n:buf的长度
         * flag:标志位————0代表阻塞、MSG_DONTWAIT表示非阻塞
         */
        if(send(acceptfd, buf, N, 0) < 0)
        {
            ERR_LOG("fail to send");
        }
    }

    // 第七步：关闭套接字
    close(acceptfd);
    close(sockfd);

    return 0;
}
