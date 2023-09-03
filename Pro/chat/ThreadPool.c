/******************ThreadPool.c*********************/
#include <stdio.h>   // 包含标准输入输出库的头文件
#include <stdlib.h>  // 包含标准库的头文件
#include <string.h>  // 包含字符串库的头文件
#include <pthread.h> // 包含线程库的头文件
#include <unistd.h>  // 包含 POSIX 系统调用库的头文件

#include "DoubleLinkList.h" // 包含自定义的双向链表头文件
#include "StdThread.h"      // 包含自定义的线程操作头文件
#include "ThreadPool.h"     // 包含自定义的线程池头文件
#include "LQueue.h"         // 包含自定义的队列头文件

#define true 1
#define false 0
#define Sleep_Time 10 // 线程休眠时间

typedef struct Task
{
    void *(*function)(void *);
    void *arg;
} task;

// 创建任务
task *CreateTask(void *(*func)(void *), void *arg)
{
    task *t = (task *)malloc(sizeof(task)); // 为任务分配内存
    if (t == NULL)
    {
        printf("fail to CreateTask malloc\n"); // 如果分配失败，输出错误信息
        return NULL;
    }
    t->function = func;
    t->arg = arg;
    return t;
}

// 释放任务
void FreeTask(task *t)
{
    free(t);
}

struct ThreadPool
{
    DLlist threads;    // 线程列表
    LQueue task_queue; // 任务队列

    int min_thrd_num;   // 最小线程数
    int max_thrd_num;   // 最大线程数
    int max_queue_size; // 最大队列大小
    int busy_thrd_num;  // 忙碌线程数
    int exit_thrd_num;  // 退出线程数

    pthread_mutex_t pool_mutex;      // 线程池互斥锁
    pthread_mutex_t busy_thrd_mutex; // 忙碌线程互斥锁
    pthread_cond_t queue_not_empty;  // 队列非空条件变量
    pthread_cond_t queue_not_full;   // 队列非满条件变量

    Thread *admin_thread; // 管理线程

    int shutdown; // 线程池关闭标志
};

// 线程工作函数
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

// 线程管理函数
void *thread_manager(void *arg)
{
    ThreadP *p = (ThreadP *)arg;
    while (p->shutdown != true)
    {
        sleep(Sleep_Time);
        pthread_mutex_lock(&p->pool_mutex);

        // 创建线程
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

        // 销毁线程
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
    pthread_exit(NULL); // 退出管理线程
}

// 初始化线程池
ThreadP *InitThreadPool(int max_thrd_num, int min_thrd_num, int max_queue_num)
{
    ThreadP *p = (ThreadP *)malloc(sizeof(ThreadP)); // 为线程池分配内存
    if (p == NULL)
    {
        printf("fail to InitThreadPool\n"); // 如果分配失败，输出错误信息
        return NULL;
    }

    InitDLlist(&p->threads);    // 初始化线程列表
    InitLQueue(&p->task_queue); // 初始化任务队列

    p->max_thrd_num = max_thrd_num;    // 设置最大线程数
    p->min_thrd_num = min_thrd_num;    // 设置最小线程数
    p->max_queue_size = max_queue_num; // 设置最大队列大小
    p->busy_thrd_num = 0;              // 忙碌线程数初始为0
    p->exit_thrd_num = 0;              // 退出线程数初始为0

    pthread_mutex_init(&p->pool_mutex, NULL);      // 初始化线程池互斥锁
    pthread_mutex_init(&p->busy_thrd_mutex, NULL); // 初始化忙碌线程互斥锁
    pthread_cond_init(&p->queue_not_empty, NULL);  // 初始化队列非空条件变量
    pthread_cond_init(&p->queue_not_full, NULL);   // 初始化队列非满条件变量

    p->shutdown = false; // 初始化关闭标志为false

    for (int i = 0; i < p->max_thrd_num; i++) // 创建初始线程
    {
        Thread *t = InitThread(thread_worker, p);
        InsertTail(&p->threads, t);
    }

    p->admin_thread = InitThread(thread_manager, p); // 创建管理线程
    return p;
}

// 向线程池添加任务
void ThreadP_AddTask(ThreadP *p, void *(*func)(void *), void *arg)
{
    pthread_mutex_lock(&p->pool_mutex);
    while (IsQEmpty(&p->task_queue) == p->max_queue_size) // 如果任务队列已满
    {
        pthread_cond_wait(&p->queue_not_full, &p->pool_mutex); // 等待队列非满条件
    }
    if (p->shutdown == true) // 如果线程池已关闭
    {
        pthread_mutex_unlock(&p->pool_mutex); // 解锁并返回
        return;
    }
    QPush(&p->task_queue, CreateTask(func, arg)); // 将任务推入队列
    pthread_cond_broadcast(&p->queue_not_empty);  // 唤醒等待队列非空的线程
    pthread_mutex_unlock(&p->pool_mutex);         // 解锁
}

// 销毁线程池
void DestoryThreadPool(ThreadP *p)
{
    if (p == NULL)
    {
        return;
    }
    p->shutdown = true; // 设置线程池关闭标志

    JoinThread(p->admin_thread); // 等待管理线程结束
    free(p->admin_thread);       // 释放管理线程资源

    int len = GetListLen(&p->threads); // 获取线程列表长度
    for (int i = 0; i < len; i++)      // 唤醒所有等待线程
    {
        pthread_cond_broadcast(&p->queue_not_empty);
    }

    LNode *travelPoint = p->threads.head; // 遍历线程列表
    while (travelPoint != NULL)           // 等待所有线程结束并释放资源
    {
        Thread *t = (Thread *)travelPoint->data;
        JoinThread(t);
        free(t);
        travelPoint = travelPoint->next;
    }
    FreeDLlist(&p->threads); // 释放线程列表资源

    while (IsQEmpty(&p->task_queue) != true) // 清空任务队列
    {
        task *t = (task *)(LQPop(&p->task_queue));
        free(t);
    }
    FreeQueue(&p->task_queue); // 释放任务队列资源

    pthread_mutex_destroy(&p->pool_mutex);      // 销毁线程池互斥锁
    pthread_mutex_destroy(&p->busy_thrd_mutex); // 销毁忙碌线程互斥锁

    pthread_cond_destroy(&p->queue_not_empty); // 销毁队列非空条件变量
    pthread_cond_destroy(&p->queue_not_full);  // 销毁队列非满条件变量
}
