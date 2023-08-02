#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>

//创建TCP套接字
int main(int argc, const *argv[])
{
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("fail to socket");
        exit(1);
    }

    printf("sockfd = %d\n", sockfd);
    return 0;
}