#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "DoubleLinkList.h"
#include "StdThread.h"
#include "ThreadPool.h"
#include "LQueue.h"

#define true 1
#define false 0
#define Sleep_Time 10

typedef struct Task
{
    void *(*function)(void *);
    void *arg;
} task;

task *CreateTask(void *(*func)(void *), void *arg)
{
    task *t = (task *)malloc(sizeof(task));
    if (t == NULL)
    {
        printf("fail to CreateTask malloc\n");
        return NULL;
    }
    t->function = func;
    t->arg = arg;
    return t;
}
void FreeTask(task *t)
{
    free(t);
}

struct ThreadPool
{
    DLlist threads;
    LQueue task_queue;

    int min_thrd_num;
    int max_thrd_num;
    int max_queue_size;
    int busy_thrd_num;
    int exit_thrd_num;

    pthread_mutex_t pool_mutex;
    pthread_mutex_t busy_thrd_mutex;
    pthread_cond_t queue_not_empty;
    pthread_cond_t queue_not_full;

    Thread *admin_thread;

    int shutdown;
};

void *thread_worker(void *arg)
{
    ThreadP *p = (ThreadP *)arg;
    while (1)
    {
        pthread_mutex_lock(&p->pool_mutex);

        while (IsQEmpty(&p->task_queue) == true && p->shutdown == false)
        {
            pthread_cond_wait(&p->queue_not_empty, &p->pool_mutex);

            if (p->exit_thrd_num > 0)
            {
                p->exit_thrd_num--;

                LNode *TravelPoint = p->threads.head;
                while (TravelPoint != NULL)
                {
                    Thread *t = (Thread *)TravelPoint->data;
                    if (GetThreadId(t) == pthread_self())
                    {
                        RemoveByElement(&p->threads, t);
                        break;
                    }
                    TravelPoint = TravelPoint->next;
                }
                pthread_mutex_unlock(&p->pool_mutex);
                pthread_exit(NULL);
            }
        }

        if (p->shutdown == true)
        {
            pthread_mutex_unlock(&p->pool_mutex);
            pthread_exit(NULL);
        }
        task *tk = (task *)(*LQPop(&p->task_queue));
        pthread_mutex_unlock(&p->pool_mutex);

        pthread_cond_broadcast(&p->queue_not_full);

        pthread_mutex_lock(&p->busy_thrd_mutex);
        p->busy_thrd_num++;
        pthread_mutex_unlock(&p->busy_thrd_mutex);

        tk->function(tk->arg);

        pthread_mutex_lock(&p->busy_thrd_mutex);
        p->busy_thrd_num--;
        pthread_mutex_unlock(&p->busy_thrd_mutex);

        FreeTask(tk);
    }
}

void *thread_manager(void *arg)
{
    ThreadP *p = (ThreadP *)arg;
    while (p->shutdown != true)
    {
        sleep(Sleep_Time);
        pthread_mutex_lock(&p->pool_mutex);

        // create
        int queueLen = GetLQueueLen(&p->task_queue);
        int thread_num = GetListLen(&p->threads);
        if (p->busy_thrd_num < GetLQueueLen(&p->task_queue) && GetListLen(&p->threads) < p->max_thrd_num)
        {
            int add = (queueLen / 2) > (p->max_thrd_num - thread_num) ? (p->max_thrd_num - thread_num) : (queueLen / 2);
            for (int i = 0; i < add; i++)
            {
                Thread *t = InitThread(thread_worker, p);
                InsertTail(&p->threads, t);
            }
        }

        // destory
        if (thread_num > p->busy_thrd_num * 2 && thread_num > p->min_thrd_num)
        {
            int minus_thrd_num = (thread_num - p->busy_thrd_num) / 2;
            int minus = minus_thrd_num > (thread_num - p->min_thrd_num) ? (thread_num - p->min_thrd_num) : minus_thrd_num;

            p->exit_thrd_num = minus;
            pthread_mutex_unlock(&p->pool_mutex);
            for (int i = 0; i < minus; i++)
            {
                pthread_cond_broadcast(&p->queue_not_empty);
            }
            continue;
        }

        pthread_mutex_unlock(&p->pool_mutex);
    }
    pthread_exit(NULL); //
}

ThreadP *InitThreadPool(int max_thrd_num, int min_thrd_num, int max_queue_num)
{
    ThreadP *p = (ThreadP *)malloc(sizeof(ThreadP));
    if (p == NULL)
    {
        printf("fail to InitThreadPool\n");
        return NULL;
    }

    InitDLlist(&p->threads);
    InitLQueue(&p->task_queue);

    p->max_thrd_num = max_thrd_num;
    p->min_thrd_num = min_thrd_num;
    p->max_queue_size = max_queue_num;
    p->busy_thrd_num = 0;
    p->exit_thrd_num = 0;

    pthread_mutex_init(&p->pool_mutex, NULL);
    pthread_mutex_init(&p->busy_thrd_mutex, NULL);
    pthread_cond_init(&p->queue_not_empty, NULL);
    pthread_cond_init(&p->queue_not_full, NULL);

    p->shutdown = false;

    for (int i = 0; i < p->max_thrd_num; i++)
    {
        Thread *t = InitThread(thread_worker, p);
        InsertTail(&p->threads, t);
    }

    p->admin_thread = InitThread(thread_manager, p);
    return p;
}

void ThreadP_AddTask(ThreadP *p, void *(*func)(void *), void *arg)
{
    pthread_mutex_lock(&p->pool_mutex);
    while (IsQEmpty(&p->task_queue) == p->max_queue_size)
    {
        pthread_cond_wait(&p->queue_not_full, &p->pool_mutex);
    }
    if (p->shutdown == true)
    {
        pthread_mutex_unlock(&p->pool_mutex);
        return;
    }
    QPush(&p->task_queue, CreateTask(func, arg));
    pthread_cond_broadcast(&p->queue_not_empty);
    pthread_mutex_unlock(&p->pool_mutex);
}

void DestoryThreadPool(ThreadP *p)
{
    if (p == NULL)
    {
        return;
    }
    p->shutdown = true;

    JoinThread(p->admin_thread);
    free(p->admin_thread);

    int len = GetListLen(&p->threads);
    for (int i = 0; i < len; i++)
    {
        pthread_cond_broadcast(&p->queue_not_empty);
    }

    LNode *travelPoint = p->threads.head;
    while (travelPoint != NULL)
    {
        Thread *t = (Thread *)travelPoint->data;
        JoinThread(t);
        free(t);
        travelPoint = travelPoint->next;
    }
    FreeDLlist(&p->threads);

    while (IsQEmpty(&p->task_queue) != true)
    {
        task *t = (task *)(LQPop(&p->task_queue));
        free(t);
    }
    FreeQueue(&p->task_queue);

    pthread_mutex_destroy(&p->pool_mutex);
    pthread_mutex_destroy(&p->busy_thrd_mutex);

    pthread_cond_destroy(&p->queue_not_empty);
    pthread_cond_destroy(&p->queue_not_full);
}
