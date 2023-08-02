#ifndef __STACK_H_
#define __STACK_H_
#include <stdio.h>
#include <stdlib.h>

#define GrowFactor 2
#define ElementType int

struct Stack
{
    ElementType *stack;
    int len;
    int capacity;
};
typedef struct Stack DMStack;

void InitStack(DMStack *s, int capacity);

void FreeStack(DMStack *s);

// void ReallocStack(DMStack *s, int newCapacity);
void ReallocStack(DMStack *s);

void Push(struct Stack *s, ElementType element);

ElementType *Pop(DMStack *s);

#endif