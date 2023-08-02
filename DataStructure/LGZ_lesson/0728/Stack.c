#include <stdio.h>

#define ElemenType int
#define Max 10

struct Stack
{
    ElemenType stack[Max];
    int len;
};

void Push(struct Stack *s, ElemenType element)
{
    if (s->len >= Max)
    {
        printf("stack is full!\n");
        return;
    }

    s->stack[s->len] = element;
    s->len++;
}

ElemenType *Pop(struct Stack *s)
{
    if (s->len <= 0)
    {
        printf("stack is empty!\n");
        return NULL;
    }

    s->len--;
    return &s->stack[s->len];
}

int main(int argc, char *argv[])
{
    struct Stack s;
    s.len = 0;

    // for (int i = 0; i < 10; i++)
    // {
    //     Push(&s, i + 1);
    // }

    // while(s.len != 0)
    // {
    //     printf("%d ", *Pop(&s));
    // }
    // printf("\n");

//进制转换
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
        if(temp <= 9)
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

    while(s.len != 0)
    {
        printf("%c", *Pop(&s));
        // printf("%c ", Map[*Pop(&s)]);
    }
    printf("\n");
#endif
    return 0;
}
