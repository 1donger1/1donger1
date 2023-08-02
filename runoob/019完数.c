#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main(int argc, char *argv[])
{
    int i, j, k, n, sum;
    int a[256];

    // 从2开始遍历整数，找出所有完全数并输出它们的因子组合
    for (i = 2; i <= N; i++)
    {
        sum = a[0] = 1;//初始化总和为1，同时将第一个因子设为1
        k = 0;//初始化数组的索引为0

        //通过循环遍历2到(i/2)的整数，找出i的所有因子
        for (j = 2; j <= (i / 2); j++)
        {
            if(i%j == 0)//如果j是i的因子
            {
                sum += j;//将因子j加入总和
                a[++k] = j;//将因子j加入因子数组，并将数组索引k增加1
            }
        }

        if(i == sum)//如果i等于总和sum，则说明i是完全数
        {
            //输出完全数及其因子组合
            printf("%d=%d", i, a[0]);
            for (n = 1; n <= k;n++)
            {
                printf("+%d", a[n]);
            }
            printf("\n");
        }
    }



    return 0;
}