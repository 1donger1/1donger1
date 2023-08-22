#include <sys/socket.h> //网络进程
 #include<stdlib.h>
 #include<unistd.h>
#include<netinet/in.h>  //socket网络编程结构体在定义
#include<arpa/inet.h> //大端转小端
#include<stdio.h>


int main(int argc,char *argv[])
{  
    if(argc !=3)
    {
        printf("invalid numbers!\n");
        return -1;
    }

    int sock = socket(AF_INET,SOCK_DGRAM,0);  
     //第一个参数协议族  第二个参数套接字 数据报 : UDP    第三个参数 根据套接字 类型和协议族系统自动匹配类型
    if(sock <0)  //如果套接字获取失败
    {
        perror("socket :");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//协议族
    addr.sin_port = htons(atoi(argv[2])); //端口号  atoi 字符串转int  32转成大端
    addr.sin_addr.s_addr = inet_addr(argv[1]);//地址   inet_addr 直接转
    
    // while(1)
    // {
    //     char temp[100] = {0};
    //     scanf("%[^\n]",temp);
    //     while(getchar() !='\n'); //解决回车问题
    //     if(sendto(sock,temp,100,0,(struct sockaddr *)&addr,sizeof(addr)) < 0)
    //     {
    //         perror("sendto :");
    //     }
    // }

    if(bind(sock,(struct sockaddr *)&addr,sizeof(addr)) !=0 )  //绑自己的ip和端口号
    {
        perror("bing :");
    }
    while(1)
    {
        char buf[100] = {0};
        struct sockaddr_in clientAddr;
        socklen_t len;
        if(recvfrom(sock,buf,100,0,(struct sockaddr *)&clientAddr,&len) < 0 )//收信息
        {
            perror("recvfrom :");
        }

        printf("ip : %s port : %d \n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
        printf("content : %s\n",buf);
    }
    close(sock);
    
}