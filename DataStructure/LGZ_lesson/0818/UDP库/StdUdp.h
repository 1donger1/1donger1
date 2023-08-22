#ifndef __STDUDP_H_
#define __STDUDP_H_
#include <stddef.h>
struct UdpServer;
typedef struct UdpServer UdpS;

UdpS * InitUdpServer(const char *IP,short int port);
void UdpServerSend(UdpS *s,const  char* destIP,short int port,void*ptr ,size_t size);
void UdpServerRecv(UdpS *s,void *ptr,size_t size);
void ClearUdpServer(UdpS *s);


struct UdpClient;
typedef struct UdpClient UdpC;

UdpC * InitUdpClient(const char * serverIP,short int ServerPort);
void UdpClientSend(UdpC *c,void *ptr,size_t size);
void UdpClientRecv(UdpC *c,void * ptr,size_t size);
void ClearUdpClient(UdpC *c);

#endif
