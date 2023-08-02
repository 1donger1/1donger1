#include <stdio.h>
#include <stdlib.h>

/*
约瑟夫环问题
有n个人围成一圈，顺序排号。
从第一个人开始报数（从1到3报数），凡报到3的人退出圈子，
问最后留下的是原来第几号的那位。
*/

int main(int argc, char *argv[])
{
    int n;
    int m = 0; // 代表退出的人数
    printf("请输入人数：");
    scanf("%d", &n);

    int i = 0;
    int k = 0;
    int a[n];

    // 按顺序编号
    for (i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
    for (i = 0; i < n; i++)
    {
        printf("%-3d", a[i]);
    }
    printf("\n");

    i = 0;
    while (m < n - 1)
    {
        if (a[i] != 0)
        {
            k++;
        }
        if (k == 3)
        {
            a[i] = 0; // 将数到3的人值设置为0
            k = 0;
            m++;
        }
        i++;
        if (i == n)
        {
            i = 0; //相当于新一轮的循环
        }
    }
    printf("这个人是：");
    for (i = 0; i < n; i++)
    {
        if (a[i] != 0)
        {
            printf("%-3d", a[i]);
        }
    }

    return 0;
}

