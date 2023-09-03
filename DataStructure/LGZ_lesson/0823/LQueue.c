#include "LQueue.h"
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
int InitLQueue(LQueue *lq)
{
    return InitDLlist(&lq->queue);
}

void QPush(LQueue *lq, ElementType element)
{
    InsertTail(&lq->queue, element);
}

ElementType *LQPop(LQueue *lq)
{
    if (lq->queue.len == 0)
    {
        printf("Queue is empty!\n");
        return NULL;
    }
    lq->FrontData = lq->queue.head->data;
    RemoveByIndex(&lq->queue, 0);
    return &lq->FrontData;
}

void FreeQueue(LQueue *lq)
{
    FreeDLlist(&lq->queue);
}

int IsQEmpty(LQueue *lq)
{
    if (lq->queue.len == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return 0;
}

LNode *GetFront(LQueue *lq)
{
    return lq->queue.head;
}

int GetLQueueLen(LQueue *lq)
{
    return lq->queue.len;
}