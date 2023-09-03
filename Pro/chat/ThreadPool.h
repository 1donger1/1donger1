#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

typedef struct ThreadPool ThreadP;

ThreadP *InitThreadPool(int max_thrd_num, int min_thrd_num, int max_queue_num);

void ThreadP_AddTask(ThreadP *p, void *(*func)(void *), void *arg);

void DestoryThreadPool(ThreadP *p);

#endif