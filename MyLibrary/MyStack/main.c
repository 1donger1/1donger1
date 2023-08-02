#include "Stack.h"

int main(int argc, char *argv[])
{
    /*********************************************************/
    DMStack s;
    InitStack(&s, 10);
#if 1
    for (int i = 0; i < 21; i++)
    {
        Push(&s, i + 1);
    }

    while (s.len != 0)
    {
        printf("%d ", *Pop(&s));
    }
    printf("\n");

    
#endif
// 进制转换
#if 1
    int num = 0;
    printf("please input your number:");
    scanf("%d", &num);

    int n = 0;
    printf("please input a system num:");
    scanf("%d", &n);

    // char Map[] = "0123456789ABCDEF";
    while (num != 0)
    {
        int temp = num % n;
        if (temp <= 9)
        {
            temp = temp + '0';
        }
        else
        {
            temp = temp - 10 + 'A';
        }
        Push(&s, temp);
        num = num / n;
    }

    printf("转换结果为：");
    if (n == 16)
    {
        printf("0X ");
    }

    while (s.len != 0)
    {
        printf("%c", *Pop(&s));
        // printf("%c ", Map[*Pop(&s)]);
    }
    printf("\n");
#endif
    FreeStack(&s);
    return 0;
}