#include "001StdThread.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#if 0
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int money = 10000;
void *zhangsan(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("zhangsan current money :%d\n", money);

    int MyMoney = money;
    printf("zhangsan want to take money!\n");
    sleep(1);

    if (MyMoney >= 10000)
    {
        money = 0;
        printf("zhangsan get money 10000! current rest : 0\n");
    }
    else
    {
        printf("zhangsan has no money!\n");
    }
    pthread_mutex_unlock(&mutex);
}

void *lisi(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("lisi current money :%d\n", money);

    int MyMoney = money;
    printf("lisi want to take money!\n");
    sleep(1);

    if (MyMoney >= 10000)
    {
        money = 0;
        printf("lisi get money 10000! current rest : 0\n");
    }
    else
    {
        printf("lisi has no money!\n");
    }
    pthread_mutex_unlock(&mutex);
}
#endif

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int flag = 0;
void *Print1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (flag == 0)
        {
            printf("A\n");
            sleep(1);
            flag = 1;
            pthread_cond_signal(&cond);
        }
        else
        {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void *Print2(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (flag == 1)
        {
            printf("B\n");
            sleep(1);
            flag = 0;
            pthread_cond_signal(&cond);
        }
        else
        {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[])
{
    // pthread_mutex_init(&mutex, NULL);
    // Thread *t1 = InitThread(zhangsan, NULL);
    // Thread *t2 = InitThread(lisi, NULL);

    Thread *t1 = InitThread(Print1, NULL);
    Thread *t2 = InitThread(Print2, NULL);
    JoinThread(t1);
    JoinThread(t2);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    // pthread_mutex_destroy(t1);
    return 0;
}