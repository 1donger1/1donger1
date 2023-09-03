#include <sys/socket.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

/* 
    SOCK_RAW:原始套接字:实现来源于内核
    用它可以查看自己的网卡信息，流量信息


    以太网首部:6个字节的目标MAC， 6个字节的源MAC 2帧的类型
    28个字节的ARP 
        硬件类型2个,
        协议类型2,
        硬件地址长度1,
        协议地址长度1 or 2,
        源MAC 6个,
        源IP 4个，
        目标IP 4个

    openssl:开源加密库

    对称加密:加密和解密是同一把钥匙
    非对称加密:加密和解密是两把钥匙--公钥 密钥 
    中间人攻击
*/

int main(int argc, char *argv[])
{

    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    while (1)
    {
        unsigned char str[1600] = {0};
        recv(sock, str, 1600, 0);

        unsigned char dst_mac[18] = {0};
        unsigned char src_mac[18] = {0};

        sprintf(dst_mac, "%x:%x:%x:%x:%x:%x", str[0], str[1], str[2], str[3], str[4], str[5]);
        sprintf(src_mac, "%x:%x:%x:%x:%x:%x", str[6], str[7], str[8], str[9], str[10], str[11]);

        printf("src mac:%s ---> dst mac:%s\n", src_mac, dst_mac);
    }

    return 0;
}