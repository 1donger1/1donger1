#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    long ge, shi, qian, wan, x;
    printf("请输入5位数:");
    scanf("%ld", &x);

    wan = x / 10000;
    qian = x % 10000 / 1000;
    shi = x % 100 / 10;
    ge = x % 10;

    if (ge == wan && shi == qian)
    {
        printf("这是回文数\n");
    }
    else
    {
        printf("这不是回文数\n");
    }
    return 0;
}