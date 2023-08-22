#include<arpa/inet.h>
#include<stdio.h>

int main()
{
    // int a= 0x01020304;
    // short int b = 0x0102;
    // printf("a = %x\n",htonl(a));
    // printf("b = %x\n",htons(b));
    // return 0;

    //**********************************

    char ip[] = "10.0.1.20";
    unsigned int a = 0;

    inet_pton(AF_INET,ip,&a);

    printf("a = %u\n",a);

    unsigned char * p = &a;
    printf("%d %d %d %d\n",*p,*(p+1),*(p+2),*(p+3));

    //******************************************UDP
    
}