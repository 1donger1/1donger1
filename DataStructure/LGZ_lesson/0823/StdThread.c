#include "StdThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct StdThread
{
    pthread_t threadID;
};

Thread *InitThread(void *(*func)(void *), void *arg)
{
    Thread *t = (Thread *)malloc(sizeof(Thread));
    if(t == NULL)
    {
        printf("InitThread malloc fail\n");
        return NULL;
    }
    if(pthread_create(&t->threadID, NULL, func, arg) != 0)
    {
        perror("InitThread pthread_create\n");
        free(t);
        return NULL;
    }
    return t;
}

void *JoinThread(Thread *t)
{
    void *value = NULL;
    pthread_join(t->threadID, &value);
    return value;
}

void DetachTherad(Thread *t)
{
    if(pthread_detach(t->threadID) != 0)
    {
        perror("fail to DetachTherad\n");
        return;
    }
}

void CancelThread(Thread *t)
{
    if(pthread_cancel(t->threadID) != 0)
    {
        perror("fail to CancelThread");
        return;
    }
}

void ClearThread(Thread *t)
{
    free(t);
}

unsigned long int GetThreadId(Thread *t)
{
    return t->threadID;
}
