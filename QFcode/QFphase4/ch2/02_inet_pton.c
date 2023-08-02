#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    char ip_str[] = "192.168.19.131";
    unsigned int ip_int = 0;
    unsigned char *ip_p = NULL;//为方便之后逐个字节输出内容

    // 将点分十进制ip地址转化为32位无符号整形数据
    inet_pton(AF_INET, ip_str, &ip_int);

    printf("ip_int = %u\n", ip_int);

    ip_p = (char *)&ip_int;
    printf("in_uint = %u,%u,%u,%u\n", *ip_p, *(ip_p + 1), *(ip_p + 2), *(ip_p + 3));

    return 0;
}