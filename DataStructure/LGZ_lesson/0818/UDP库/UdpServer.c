#include <sys/socket.h> //网络进程
 #include<stdlib.h>
 #include<unistd.h>
#include<netinet/in.h>  //socket网络编程结构体在定义
#include<arpa/inet.h> //大端转小端
#include<stdio.h>
#include"StdUdp.h"


int main(int argc,char *argv[])
{  
    if(argc !=3)
    {
        printf("invalid numbers!\n");
        return -1;
    }

    UdpS * s = InitUdpServer(argv[1],atoi(argv[2]));

    while(1)
    {
        char temp[100] = {0};
        UdpServerRecv(s,temp,100);
        printf("recv from : %s\n",temp);
    }

    ClearUdpServer(s);
    return 0;
    
}