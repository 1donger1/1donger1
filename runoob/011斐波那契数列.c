#include <stdio.h>
#include <stdlib.h>

// 古典问题（兔子生崽）：有一对兔子，从出生后第3个月起每个月都生一对兔子，
// 小兔子长到第三个月后每个月又生一对兔子，假如兔子都不死，
// 问每个月的兔子总数为多少？（输出前40个月即可）

// 分析：兔子的规律为数列1,1,2,3,5,8,13,21....，即下个月是上两个月之和（从第三个月开始）。

#include <stdio.h>

#include <stdio.h>

int fibonaci(int i)
{
    if (i == 0)
    {
        return 0;
    }
    if (i == 1)
    {
        return 1;
    }
    return fibonaci(i - 1) + fibonaci(i - 2);
}

int main()
{
    int i;
    printf("month\tnumber\n");
    for (i = 1; i < 41; i++)
    {
        printf("%d\t%d\n", i, fibonaci(i));
    }

    return 0;
}
