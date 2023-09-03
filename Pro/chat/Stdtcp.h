#ifndef _STDTCP_H_
#define _STDTCP_H_
#include <stddef.h>

struct TcpServer;
typedef struct TcpServer TcpS;

TcpS *InitTcpServer(const char *ip, short int port);

int TcpServerAccept(TcpS *s);

void TcpServerSend(int ClientSock, void *ptr, size_t size);

void TcpServerRecv(int ClientSock, void *ptr, size_t size);

void ClearTcpServer(TcpS *s);

/*******************************Client***********************************/
struct TcpClient;
typedef struct TcpClient TcpC;

TcpC *InitTcpClient(const char *ServerIp, short int ServerPort);

void TcpClientSend(TcpC *c, void *ptr, size_t size);

void TcpClientRecv(TcpC *c, void *ptr, size_t size);

void ClearTcpClient(TcpC *c);
#endif