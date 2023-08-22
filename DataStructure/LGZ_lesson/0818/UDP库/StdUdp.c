#include"StdUdp.h"
#include<string.h>
#include <sys/socket.h> //网络进程
 #include<stdlib.h>
 #include<unistd.h>
#include<netinet/in.h>  //socket网络编程结构体在定义
#include<arpa/inet.h> //大端转小端
#include<stdio.h>

struct UdpServer//服务端   定义了UDP服务器的结构体，包括一个套接字成员 sock。
{
    int sock;//套接字
};

UdpS *InitUdpServer(const char *IP, short int port)//初始化UDP服务器，传入服务器的IP地址和端口号作为参数，返回一个指向 UdpS 结构体的指针。
{
    UdpS *s= (UdpS*)malloc(sizeof(UdpS));
        if(s == NULL)
        {
            printf("InitUdpServer malooc error!\n");
            return NULL;
        }

    s->sock = socket(AF_INET,SOCK_STREAM,0);  
     //第一个参数协议族  第二个参数套接字 数据报 : UDP    第三个参数 根据套接字 类型和协议族系统自动匹配类型
    if(s->sock <0)  //如果套接字获取失败
    {
        perror("socket :");
        free(s);
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//协议族
    addr.sin_port = htons(port); //端口号  atoi 字符串转int  32转成大端
    addr.sin_addr.s_addr = inet_addr(IP);//地址   inet_addr 直接转
    
    if(bind(s->sock,(struct sockaddr *)&addr,sizeof(addr)) !=0 )  //绑自己的ip和端口号
    {
        perror("bind :");
        free(s);
        return NULL;
    }
    return s;
}

void UdpServerSend(UdpS *s,const  char* destIP,short int port,void*ptr ,size_t size)
//向指定的目标IP地址和端口号发送数据，通过给定的UDP服务器套接字 s 进行发送。
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(destIP);

    if(sendto(s->sock,ptr,size,0,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("UdpServerSend sendto:  ");
    }
}

void UdpServerRecv(UdpS *s,void *ptr, size_t size)
//从UDP服务器接收数据，通过给定的UDP服务器套接字 s 进行接收，并将接收到的数据存储在 ptr 指向的缓冲区中。
{
    struct sockaddr_in addr;
    socklen_t len;
    if(recvfrom(s->sock,ptr,size,0,(struct sockaddr*)&addr,&len) < 0)
    {
        perror("UdpServerRecv recvfrom:");
    }
}

void ClearUdpServer(UdpS *s)//释放UDP服务器，关闭套接字并释放内存
{
    close(s->sock);//关闭套接字
    free(s);
}



struct UdpClient//定义了UDP客户端的结构体，包括一个套接字成员 sock 和服务端的IP地址和端口号。
{
    int sock;//套接字
    char ServerIP[20];
    short int ServerPort;
    
};


UdpC *InitUdpClient(const char *serverIP, short int ServerPort)
//初始化UDP客户端，传入服务器的IP地址和端口号作为参数，返回一个指向 UdpC 结构体的指针。
{

    UdpC *c= (UdpC*)malloc(sizeof(UdpS));
        if(c == NULL)
        {
            printf("InitUdpServer malooc error!\n");
            return NULL;
        }

    c->sock = socket(AF_INET,SOCK_STREAM,0);  
     //第一个参数协议族  第二个参数套接字 数据报 : UDP    第三个参数 根据套接字 类型和协议族系统自动匹配类型
    if(c->sock <0)  //如果套接字获取失败
    {
        perror("socket :");
        free(c);
        return NULL;
    }

    strcpy(c->ServerIP,serverIP);
    c->ServerPort = ServerPort;
    return c;

    
}

void UdpClientSend(UdpC *c, void *ptr, size_t size)//向服务器发送数据，通过给定的UDP客户端结构体指针 c 进行发送。
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(c->ServerPort);
    addr.sin_addr.s_addr = inet_addr(c->ServerIP);

    if(sendto(c->sock,ptr,size,0,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("UdpServerSend sendto:  ");
    }
}

void UdpClientRecv(UdpC *c, void *ptr, size_t size)
//从服务器接收数据，通过给定的UDP客户端结构体指针 c 进行接收，并将接收到的数据存储在 ptr 指向的缓冲区中。
{
     struct sockaddr_in addr;
    socklen_t len;
    if(recvfrom(c->sock,ptr,size,0,(struct sockaddr*)&addr,&len) < 0)
    {
        perror("UdpServerRecv recvfrom:");
    }
}

void ClearUdpClient(UdpC *c)//释放UDP客户端，关闭套接字并释放内存。
{
    close(c->sock);
    free(c);
}

