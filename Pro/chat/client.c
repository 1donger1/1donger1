/********************client.c***************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h> //网络传输数据，放结构体地址
#include "Stdtcp.h"
#include "DoubleLinkList.h"
#include "StdThread.h"

typedef struct Message
{
    int flag;
    char fromName[20];
    char toName[20];
    char content[1024];
} Msg;

void *thread_handler(void *arg)
{
    TcpC *c = (TcpC *)arg;
    while (1)
    {
        Msg msg;
        TcpClientRecv(c, &msg, sizeof(msg));
        printf("recv from [%s] message : %s\n", msg.fromName, msg.content);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("invaild number!\n");
        return -1;
    }

    TcpC *c = InitTcpClient(argv[1], atoi(argv[2]));
    if (c == NULL)
    {
        printf("client point is NULL\n");
        ClearTcpClient(c);
        return -1;
    }

    Msg msg;
    msg.flag = 1; // 1代表我的名字
    printf("Please input your name:\n");
    scanf("%[^\n]", msg.fromName);
    while (getchar() != '\n')
        ;

    TcpClientSend(c, &msg, sizeof(msg));

    Thread *t = InitThread(thread_handler, c);

    msg.flag = 2;
    while (1)
    {
        printf("1.chat to one.\n");
        printf("2.chat to all.\n");
        scanf("%d", &msg.flag);
        while (getchar() != '\n')
            ;
        msg.flag += 1;

        if (msg.flag == 2)
        {
            printf("Please input your send to name:\n");
            scanf("%[^\n]", msg.toName); // 发给的人
            while (getchar() != '\n')
                ;

            printf("Please input your send content:\n");
            scanf("%[^\n]", msg.content); // 发的内容
            while (getchar() != '\n')
                ;
            TcpClientSend(c, &msg, sizeof(msg));
        }
        else
        {
            printf("Please input your send content:\n");
            scanf("%[^\n]", msg.content); // 发的内容
            while (getchar() != '\n')
                ;
            TcpClientSend(c, &msg, sizeof(msg));
        }
    }

    return 0;
}
