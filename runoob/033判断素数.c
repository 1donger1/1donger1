#include <stdio.h>
#include <stdbool.h>
#include <math.h>
/*
题目：判断一个数字是否为质数。
程序分析：质数（prime number）又称素数，有无限个。
一个大于1的自然数，除了1和它本身外，不能被其他自然数整除。
*/

bool Is_prime(int num)
{
    if (num <= 1)
    {
        return false;
    }

    // for (int i = 2; i <= sqrt(num); i++)//用<=是考虑质数可以是完全平方数
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    int num;
    printf("请输入一个正整数: ");
    scanf("%d", &num);

    if (Is_prime(num))
    {
        printf("%d 是素数\n", num);
    }
    else
    {
        printf("%d 不是素数\n", num);
    }

    return 0;
}
