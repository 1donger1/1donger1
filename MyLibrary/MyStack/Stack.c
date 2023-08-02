#include "Stack.h"

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