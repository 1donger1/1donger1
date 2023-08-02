#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned char ip_int[] = {192, 168, 19, 131};
    char ip_str[16] = "";
    inet_ntop(AF_INET, &ip_int, ip_str, 16);
    printf("ip_s = %s\n", ip_str);

    return 0;
}

/**
 * const char *inet_ntop(int __af, const void *__restrict__ __cp, char *__restrict__ __buf, socklen_t __len)
 * 功能：整型数据转字符串转字符串格式IP地址
 */