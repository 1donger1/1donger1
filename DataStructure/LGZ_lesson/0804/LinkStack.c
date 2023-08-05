#include "LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


/// @brief 初始化栈
/// @param s 栈的指针
/// @return 
int InitLStack(LStack *s)
{
    return InitDLlist(&s->stack);
}

LNode *GetTop(LStack *s)
{
    return s->stack.tail;
}

void Push(LStack *s, ElementType element)
{
    InsertTail(&s->stack, element);
}

ElementType* Pop(LStack *s)
{
    LNode *Top = GetTop(s);
    if (s->stack.len == 0)
    {
        printf("the Stack is Empty!\n");
        return NULL;
    }
    s->TopElement =Top->data;
    RemoveByIndex(&s->stack, s->stack.len - 1);
    return &s->TopElement;
}

int IsEmpty(LStack *s)
{
    if (s->stack.len == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void StackTrave(LStack *s)
{
    Trave(&s->stack);
}

