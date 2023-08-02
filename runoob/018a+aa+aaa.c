#include <stdio.h>
#include <stdlib.h>

/*
求s=a+aa+aaa+aaaa+aa...a的值，其中a是一个数字。
例如2+22+222+2222+22222(此时共有5个数相加)，几个数相加有键盘控制。
*/

#include <stdio.h>

#if 0
int main()
{
    int s = 0, a, n, t;
    printf("请输入 a 和 n:\n");
    scanf("%d%d", &a, &n);
    t = a;
    while (n > 0)
    {
        s += t;
        a = a * 10;
        t += a;
        n--;
    }
    printf("a+aa+...=%d\n", s);
    return 0;
}
#endif

#if 0
// ChatGPT计算数列的和
int calculateSum(int a, int num_terms)
{
    int current_term = a; // 当前项的数值，初始值为 a
    int total_sum = 0;    // 总和，初始值为 0

    // 使用循环计算每一项的值并累加到总和中
    for (int i = 1; i <= num_terms; i++)
    {
        total_sum += current_term;            // 将当前项加到总和中
        current_term = current_term * 10 + a; // 更新当前项的值，将 a 加在末尾构造下一项
    }

    return total_sum; // 返回计算得到的总和
}

int main()
{
    int a, num_terms;
    printf("请输入数字 a 的值：");
    scanf("%d", &a); // 输入 a 的值

    printf("请输入要相加的项数：");
    scanf("%d", &num_terms); // 输入要相加的项数

    int result = calculateSum(a, num_terms); // 调用函数计算总和
    printf("结果为：%d\n", result);          // 输出结果

    return 0;
}
#endif


// Chatgpt计算数列的和并输出
void calculateAndPrintSum(int a, int num_terms)
{
    int current_term = a; // 当前项的数值，初始值为 a
    int total_sum = 0;    // 总和，初始值为 0

    printf("计算结果为：");

    // 使用循环计算每一项的值并累加到总和中
    for (int i = 1; i <= num_terms; i++)
    {
        total_sum += current_term; // 将当前项加到总和中

        // 打印当前项的值
        printf("%d", current_term);

        // 如果不是最后一项，则打印加号和空格
        if (i != num_terms)
        {
            printf(" + ");
        }

        current_term = current_term * 10 + a; // 更新当前项的值，将 a 加在末尾构造下一项
    }

    // 打印等号和总和
    printf(" = %d\n", total_sum);
}

int main()
{
    int a, num_terms;
    printf("请输入数字 a 的值：");
    scanf("%d", &a); // 输入 a 的值

    printf("请输入要相加的项数：");
    scanf("%d", &num_terms); // 输入要相加的项数

    calculateAndPrintSum(a, num_terms); // 调用函数计算并输出结果

    return 0;
}
