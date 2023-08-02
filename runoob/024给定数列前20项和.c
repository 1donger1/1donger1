#include <stdio.h>
#include <stdlib.h>

/*
有一分数序列：2/1，3/2，5/3，8/5，13/8，21/13...
求出这个数列的前20项之和。
*/

int main(int argc, char *argv[])
{
    float f1 = 1, f2 = 2;
    float sum = 0;
    int i, t;

    for (i = 1; i <= 20; i++)
    {
        sum = sum + f2 / f1;
        t = f2;
        f2 = f1 + f2;
        f1 = t;
    }

    printf("%9.6f\n",sum);

    return 0;
}