#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "DoubleLinkList.h"

typedef struct LinkQueue
{
    DLlist queue;
    ElementType FrontData;
} LQueue;

int InitLQueue(LQueue *lq);

void QPush(LQueue *lq, ElementType element);

ElementType *LQPop(LQueue *lq);

void FreeQueue(LQueue *lq);

int IsQEmpty(LQueue *lq);

LNode *GetFront(LQueue *lq);

#endif