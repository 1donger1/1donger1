#ifndef __LINKSTACK_H_
#define __LINKSTACK_H_
#define true 1
#define false 0
#include "DoubleLinkList.h"

// #define ElementType int

typedef struct LinkStack
{
    DLlist stack;
    ElementType TopElement;
} LStack;

int InitLStack(LStack *s);

LNode *GetTop(LStack *s);

int IsEmpty(LStack *s);

// void StackTrave(LStack *s);

void Push(LStack *s, ElementType element);

ElementType* Pop(LStack *s);

void FreeLStack(LStack *s);

#endif