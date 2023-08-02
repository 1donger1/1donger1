#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
int pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutexattr_t *attr)；
功能：初始化一个互斥锁。
参数：
mutex：互斥锁地址。
attr：互斥锁的属性，NULL 为默认的属性。
返回值：
成功返回 0，失败返回非 0。

int pthread_mutex_lock(pthread_mutex_t *mutex);
功能：对互斥锁上锁，若已经上锁，则调用者一直阻塞到互斥锁解锁。
参数：
mutex：互斥锁地址。
返回值：
成功返回 0，失败返回非 0。

int pthread_mutex_trylock(pthread_mutex_t *mutex);
功能：对互斥锁上锁，若已经上锁，则上锁失败，函数立即返回。
参数：
mutex：互斥锁地址。
返回值：
成功返回 0，失败返回非 0。

int pthread_mutex_unlock(pthread_mutex_t * mutex);
功能：对指定的互斥锁解锁。
参数：
mutex：互斥锁地址。
返回值：
成功返回 0,失败返回非 0。

int pthread_mutex_destroy(pthread_mutex_t *mutex);
功能：销毁指定的一个互斥锁。
参数：
mutex：互斥锁地址。
返回值：
成功返回 0，失败返回非 0。
*/

int money = 10000;

void *pthread_fun1(void *arg)
{
    int get, yu, shiji;
    get = 10000;

    printf("张三正在查询余额...\n");
    sleep(1);
    yu = money;

    printf("张三正在取钱...\n");
    sleep(1);

    if (get > yu)
    {
        shiji = 0;
    }
    else
    {
        shiji = get;
        yu = yu - get;
        money = yu;
    }

    printf("张三想取%d元,实际取了%d元,余额为%d元\n", get, shiji, yu);

    pthread_exit(NULL);
}

void *pthread_fun2(void *arg)
{
    int get, yu, shiji;
    get = 10000;

    printf("李四正在查询余额...\n");
    sleep(1);
    yu = money;

    printf("李四正在取钱...\n");
    sleep(1);

    if (get > yu)
    {
        shiji = 0;
    }
    else
    {
        shiji = get;
        yu = yu - get;
        money = yu;
    }

    printf("李四想取%d元,实际取了%d元,余额为%d元\n", get, shiji, yu);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, pthread_fun1, NULL) != 0)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, pthread_fun2, NULL) != 0)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}