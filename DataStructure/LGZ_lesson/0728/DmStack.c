#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define GrowFactor 2

struct Stack
{
    ElementType *stack;
    int len;
    int capacity;
};
typedef struct Stack DMStack;

void InitStack(DMStack *s, int capacity)
{
    s->stack = (ElementType *)malloc(capacity * sizeof(ElementType));
    if (s->stack == NULL)
    {
        printf("InitStack malloc fail\n");
        return;
    }
    s->len = 0;
    s->capacity = capacity;
}

void FreeStack(DMStack *s)
{
    free(s->stack);
    s->len = 0;
    s->capacity = 0;
}

// void ReallocStack(DMStack *s, int newCapacity)
// {
//     printf("use RallocStack!\n");
//     ElementType *newStack = (ElementType *)realloc(s->stack, newCapacity * sizeof(ElementType));
//     if (newStack == NULL)
//     {
//         printf("ReallocStack realloc fail\n");
//         return;
//     }

//     s->stack = newStack;
//     s->capacity = newCapacity;
// }

void ReallocStack(DMStack *s)
{
    printf("use RallocStack!\n");
    ElementType *newStack = (ElementType *)realloc(s->stack, s->capacity * sizeof(ElementType) * GrowFactor);
    if (newStack == NULL)
    {
        printf("ReallocStack realloc fail\n");
        return;
    }

    s->stack = newStack;
    s->capacity = s->capacity * GrowFactor;
}

void Push(struct Stack *s, ElementType element)
{
    // 检查是否需要重新分配内存空间
    if (s->len >= s->capacity)
    {
        int newCapacity = s->capacity * 2; // 假设每次扩容为当前容量的两倍
        // ReallocStack(s, newCapacity);
        ReallocStack(s);
    }

    s->stack[s->len] = element;
    s->len++;
}

ElementType *Pop(DMStack *s)
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
    DMStack s;

    InitStack(&s, 20);

    for (int i = 0; i < 21; i++)
    {
        Push(&s, i + 1);
    }

    while (s.len != 0)
    {
        printf("%d ", *Pop(&s));
    }
    printf("\n");

    

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
