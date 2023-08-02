#include <stdio.h>
#include <stdlib.h>

/*
打印出如下图案（菱形）。

先把图形分成两部分来看待，前四行一个规律，后三行一个规律，
利用双重for循环，第一层控制行，第二层控制列。
*/

int main()
{
    int i, j, k;

    // 打印上半部分的图形
    for (i = 0; i <= 3; i++)
    {
        for (j = 0; j <= 2 - i; j++) // 打印空格，控制图形左边的空白区域
        {
            printf(" ");
        }
        for (k = 0; k <= 2 * i; k++) // 打印星号，控制图形的宽度
        {
            printf("*");
        }
        printf("\n"); // 换行，进入下一行
    }

    // 打印下半部分的图形
    for (i = 0; i <= 2; i++)
    {
        for (j = 0; j <= i; j++) // 打印空格，控制图形左边的空白区域
        {
            printf(" ");
        }
        for (k = 0; k <= 4 - 2 * i; k++) // 打印星号，控制图形的宽度
        {
            printf("*");
        }
        printf("\n"); // 换行，进入下一行
    }

    return 0;
}

#if 0
#include <stdio.h>

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void printStars(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("*");
    }
}

int main()
{
    int height, i, j;

    printf("请输入菱形的高度（奇数）：");
    scanf("%d", &height);

    if (height % 2 == 0)
    {
        printf("高度必须是奇数。\n");
        return 1;
    }

    // 上半部分（包括中间行）
    for (i = 1; i <= height; i += 2)
    {
        printSpaces((height - i) / 2);
        printStars(i);
        printf("\n");
    }

    // 下半部分
    for (i = height - 2; i >= 1; i -= 2)
    {
        printSpaces((height - i) / 2);
        printStars(i);
        printf("\n");
    }

    return 0;
}

#endif