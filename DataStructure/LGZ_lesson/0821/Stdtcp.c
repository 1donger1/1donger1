#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Stdtcp.h"

struct TcpServer
{
    int sock;
};

TcpS *InitTcpServer(const char *ip, short int port)
{
    TcpS *s = (TcpS *)malloc(sizeof(TcpS));
    if (s == NULL)
    {
        perror("fail to InitTcpServer malloc\n");
        return NULL;
    }

    s->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (s->sock < 0)
    {
        perror("fail to socket\n");
        free(s);
        return NULL;
    }

    int on = 1;
    if (setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0)
    {
        perror("fail to setsockpot\n");
        free(s);
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(s->sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        free(s);
        return NULL;
    }

    if (listen(s->sock, 10) < 0)
    {
        perror("fail to listen\n");
        free(s);
        return NULL;
    }

    return s;
}

int TcpServerAccept(TcpS *s)
{
    struct sockaddr_in addr;
    socklen_t len;
    int acceptSock = 0;
    if ((acceptSock = accept(s->sock, (struct sockaddr *)&addr, &len)) < 0)
    {
        perror("fail to TcpServerAccept accept\n");
        return -1;
    }
    return acceptSock;
}

void TcpServerSend(int ClientSock, void *ptr, size_t size)
{
    if (send(ClientSock, ptr, size, 0) < 0)
    {
        perror("fail to TcpServerSend send\n");
        return;
    }
}

void TcpServerRecv(int ClientSock, void *ptr, size_t size)
{
    if (recv(ClientSock, ptr, size, 0) < 0)
    {
        perror("fail to TcpServerRecv recv\n");
        return;
    }
}

void ClearTcpServer(TcpS *s)
{
    close(s->sock);
    free(s);
}

/*******************************Client***********************************/

struct TcpClient
{
    int sock;
};

TcpC *InitTcpClient(const char *ServerIp, short int ServerPort)
{
    TcpC *c = (TcpC *)malloc(sizeof(TcpC));
    if (c == NULL)
    {
        perror("fail to InitTcpClient malloc\n");
        return NULL;
    }

    c->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (c->sock < 0)
    {
        perror("fail to InitTcpClient sock\n");
        free(c);
        return NULL;
    }

    struct sockaddr_in ServerAddr;
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(ServerPort);
    ServerAddr.sin_addr.s_addr = inet_addr(ServerIp);
    if (connect(c->sock, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) < 0)
    {
        perror("fail to connet\n");
        free(c);
        return NULL;
    }
    return c;
}

void TcpClientSend(TcpC *c, void *ptr, size_t size)
{
    if (send(c->sock, ptr, size, 0) < 0)
    {
        perror("fail to TcpClientSend send\n");
        return;
    }
}

void TcpClientRecv(TcpC *c, void *ptr, size_t size)
{
    if (recv(c->sock, ptr, size, 0) < 0)
    {
        perror("fail to TcpClientRecv recv\n");
        return;
    }
}

void ClearTcpClient(TcpC *c)
{
    close(c->sock);
    free(c);
}
