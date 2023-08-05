#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"
#include "LQueue.h"
#define true 1
#define false 0

#if 0
struct Queue
{
    LStack inputStack;
    LStack outputStack;
};

int InitQueue(struct Queue *q)
{
    InitLStack(&q->inputStack);
    InitLStack(&q->outputStack);
    return true;
}

int IsStackQueueEmpty(struct Queue *q)
{
    if (IsEmpty(&q->inputStack) == true && IsEmpty(&q->outputStack) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void StackQueuePush(struct Queue *q, ElementType element)
{
    // if (IsStackQueueEmpty(q) == true)
    // {
    //     printf("queue is empty!\n");
    //     return NULL;
    // }
    while (IsEmpty(&q->outputStack) == false)
    {
        Push(&q->inputStack, *Pop(&q->outputStack));
    }
    Push(&q->inputStack, element);
}

ElementType *StackQueuePop(struct Queue *q)
{
    if(IsStackQueueEmpty(q) == true)
    {
        printf("queue is empty!\n");
        return NULL;
    }
    while (IsEmpty(&q->inputStack) == false)
    {
        Push(&q->outputStack, *Pop(&q->inputStack));
    }
    return Pop(&q->outputStack);
}
#endif

struct Stack
{
    LQueue queue1;
    LQueue queue2;
};

int InitStack(struct Stack *s)
{
    InitLQueue(&s->queue1);
    InitLQueue(&s->queue2);
    return true;
}

int IsQueueStackEmpty(struct Stack *s)
{
    if (s->queue1.queue.len == 0 && s->queue2.queue.len == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void QueueSatckPush(struct Stack *s, ElementType element)
{
    if (IsQEmpty(&s->queue1) == true)
    {
        QPush(&s->queue2, element);
    }
    else
    {
        QPush(&s->queue1, element);
    }
}

ElementType *QueueSatckPop(struct Stack *s)
{
    if (IsQEmpty(&s->queue1) == true)
    {
        while (s->queue2.queue.len > 1)
        {
            QPush(&s->queue1, *LQPop(&s->queue2));
        }
        return LQPop(&s->queue2);//
    }
    else
    {
        while (s->queue1.queue.len > 1)
        {
            QPush(&s->queue2, *LQPop(&s->queue1));
        }
        return LQPop(&s->queue1);//
    }
}

int main(int argc, char *argv[])
{
#if 0
    struct Queue queue;
    InitQueue(&queue);

    for (int i = 0; i < 10; i++)
    {
        StackQueuePush(&queue, i + 1);
    }

    while (IsStackQueueEmpty(&queue) == false)
    {
        printf("%d ", *StackQueuePop(&queue));
    }
#endif

    struct Stack s;
    InitStack(&s);

    for (int i = 0; i < 10; i++)
    {
        QueueSatckPush(&s, i + 1);
    }
    while (IsQueueStackEmpty(&s) == false)
    {
        printf("%d ", *QueueSatckPop(&s));
    }

    printf("\n");

    return 0;
}