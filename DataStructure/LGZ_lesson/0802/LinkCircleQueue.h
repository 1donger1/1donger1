#ifndef __LINKCIRCLEQUEUE_
#define __LINKCIRCLEQUEUE_
#include "DoubleCircleLinkList.h"

//链式循环队列
typedef struct LinkCircleQueue
{
    DCLlist queue;
    ElementType FrontData;
} LCQueue;

int InitLCQueue(LCQueue *lcq);

void Push(LCQueue *lcq, ElementType element);

ElementType *Pop(LCQueue *lcq);

int IsEmpty(LCQueue *lcq);

#endif