#include <stdio.h>
#include <stdlib.h>

/*
题目：给一个不多于5位的正整数，
要求：一、求它是几位数，二、逆序打印出各位数字。
*/

void count(int num)
{
    int digits = 0;
    // 计算数字位数
    while (num > 0)
    {
        num /= 10;
        digits++;
    }
    printf("这是一个%d位数。\n", digits);
}

int reverse(int num)
{
    if (num > 0)
    {
        printf("%d", num % 10);
        reverse(num / 10);
    }
    else
    {
        printf("\n");
    }
}

int main()
{
    // 声明变量
    int num, temp, digits = 0;

    // 输入一个不多于5位的正整数
    printf("请输入一个不多于5位的正整数:");
    scanf("%d", &num);

    count(num);

    reverse(num);
    return 0;
}
