#include <stdio.h>
#include <stdlib.h>

/*
将一个正整数分解质因数。
例如：输入90,打印出90=2*3*3*5。
*/


int main(int argc, char *argv[])
{
    int n, i; // 声明变量 n 和 i，n 用于存储用户输入的整数，i 用于循环计算因子
    printf("请输入整数: ");
    scanf("%d", &n); 
    printf("%d=", n); 

    for (i = 2; i <= n; i++) // 从 2 开始逐个尝试因子 i
    {
        while (n % i == 0) // 使用循环判断是否为 i 的因子，如果是则进入循环
        {
            printf("%d", i); // 打印因子 i
            n /= i;          // 将 n 除以 i，以便获取下一个因子
            if (n != 1)      // 如果 n 不等于 1，则意味着还有其他因子需要继续分解，输出乘号 "*"
            {
                printf("*");
            }
        }
    }
    printf("\n");

    return 0;
}
