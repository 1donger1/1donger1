#include "LinkCircleQueue.h"
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

int InitLCQueue(LCQueue *lcq)
{
    return InitDCLlist(&lcq->queue);
}

void Push(LCQueue *lcq, ElementType element)
{
    InsertTail(&lcq->queue, element);
}

ElementType *Pop(LCQueue *lcq)
{
    if(lcq->queue.len == 0)
    {
        printf("Queue is emmpty!\n");
        return NULL;
    }
    lcq->FrontData = lcq->queue.head->data;
    RemoveByIndex(&lcq->queue, 0);
    return &lcq->FrontData;
}

int IsEmpty(LCQueue *lcq)
{
    if(lcq->queue.len == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return 0;
}
