#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, num;
    num = 2;
    for (i = 0; i < 3; i++)
    {
        printf("num 变量为 %d \n", num);
        num++;
        {
            auto int num = 1;
            printf("内置模块num变量为%d\n", num);
        }
    }

    return 0;
}

/*
num 变量为 2
内置模块num变量为1
num 变量为 3
内置模块num变量为1
num 变量为 4
内置模块num变量为1
*/