#include <stdio.h>
#include <stdlib.h>

// 题目：一个整数，它加上100后是一个完全平方数，
//      再加上168又是一个完全平方数，请问该数是多少？

// 思路:x+100=n^2, x+100+168=m^2
int main(void)
{
    int i, j, m, n, x;

    for (i = 1; i < 168 / 2 + 1; i++)
    {
        if (168 % i == 0)
        {
            j = 168 / i;
            if (i > j && (i + j) % 2 == 0 && (i - j) % 2 == 0)
            {
                m = (i + j) / 2;
                n = (i - j) / 2;
                x = n * n - 100;
                printf("This num is %d\n", x);
                printf("%d + 100 = %d * %d\n", x, n, n);
                printf("%d + 268 = %d * %d\n", x, m, m);
                printf("-----------------------------\n");
            }
        }
    }

    return 0;
}