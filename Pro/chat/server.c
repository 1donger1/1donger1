/********************server.c***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h> //网络传输数据，放结构体地址

#include "Stdtcp.h"
#include "StdThread.h"
#include "DoubleLinkList.h"
#include "ThreadPool.h"

typedef struct Client
{
    int sock;
    char name[20];
} C;

C *CreateClient(int sock, const char *name)
{
    C *c = (C *)malloc(sizeof(C));
    if (c == NULL)
    {
        printf("fail to CreateClient malloc");
        return NULL;
    }
    c->sock = sock;
    strcpy(c->name, name);
    return c;
}

void FreeClient(C *c)
{
    if (c != NULL)
    {
        free(c);
    }
}

typedef struct Message
{
    int flag;
    char fromName[20];
    char toName[20];
    char content[1024];
} Msg;

DLlist list;

void *thread_handler(void *arg)
{
    int sock = *((int *)arg);
    while (1)
    {
        Msg msg;
        TcpServerRecv(sock, &msg, sizeof(msg));
        printf("recv flag:%d fromName message:%s, toName:%s Content:%s\n",
               msg.flag, msg.fromName, msg.toName, msg.content);
        switch (msg.flag)
        {
        case 1:
            InsertTail(&list, CreateClient(sock, msg.fromName));
            break;
        case 2:
            struct Node *travelPoint = list.head;
            while (travelPoint != NULL)
            {
                C *c = (C *)travelPoint->data;
                if (strcmp(c->name, msg.toName) == 0)
                {
                    TcpServerSend(c->sock, &msg, sizeof(msg));
                    break;
                }
                travelPoint = travelPoint->next;
            }
            break;
        case 3:
            struct Node *travelPoint1 = list.head;
            while (travelPoint1 != NULL)
            {
                C *c = (C *)travelPoint1->data;
                if (strcmp(c->name, msg.fromName) != 0)
                {
                    TcpServerSend(c->sock, &msg, sizeof(msg));
                }
                travelPoint1 = travelPoint1->next;
            }
            break;

        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("invaild number!\n");
        return -1;
    }
    InitDLlist(&list);

    ThreadP *p = InitThreadPool(20, 10, 10);
    if(p == NULL)
    {
        printf("fail to InitThreadPool\n");
        return -1;
    }

    TcpS *s = InitTcpServer(argv[1], atoi(argv[2]));
    if (s == NULL)
    {
        printf("server point is NULL\n");
        return -1;
    }

    int acceptSock = 0;
    while ((acceptSock = TcpServerAccept(s)) > 0)
    {
        ThreadP_AddTask(p, thread_handler, &acceptSock);
    }

    DestoryThreadPool(p);
    return 0;
}