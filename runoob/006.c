#include <stdio.h>
#include <stdlib.h>

// 用*号输出字母C的图案

int main(int argc, char *argv[])
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        printf("%c", '*');
    }
    printf("\n");
    for (i = 0; i < 2;i++)
    {
        printf("*\n");
    }
    for (i = 0; i < 4; i++)
    {
        printf("%c", '*');
    }
    printf("\n");

    return 0;
}