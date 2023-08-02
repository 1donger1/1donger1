#include <stdio.h>
#include <math.h>

// 判断 101 到 200 之间的素数。
// 判断素数的方法：用一个数分别去除 2 到 sqrt(这个数)，
// 如果能被整除，则表明此数不是素数，反之是素数。

int main(int argc, char *argv[])
{
    int i, j;
    int count = 0;
    for (i = 101; i <= 200; i++)
    {
        for (j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                break;
            }
            
        }
        if (j > sqrt(i))
        {
            count++;
            printf("%d ", i);
            if(count % 5 == 0)
            {
                printf("\n");
            }
        }   
    }
    printf("\n");

    return 0;
}
