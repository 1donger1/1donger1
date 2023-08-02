#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/*
int sem_init(sem_t *sem, int pshared, unsigned int value);
功能：
创建一个信号量并初始化它的值。
参数：
sem：信号量的地址。
pshared：等于 0，信号量在线程间共享；不等于 0，信号量在进程间共享。
value：信号量的初始值。
返回值：
成功返回 0，失败返回-1。


int sem_wait(sem_t *sem);
功能：
将信号量的值减 1，若信号量的值小于等于 0，此函数会引起调用者阻塞。
参数：
sem：信号量地址。
返回值：
成功返回 0，失败返回-1。

int sem_trywait(sem_t *sem);
功能：
将信号量的值减 1，若信号量的值小于等于 0，则对信号量的操作失败，函数立即返回。
参数：
sem：信号量地址。
返回值：
成功返回 0，失败返回-1。

int sem_post(sem_t *sem);
功能：
将信号量的值加 1 并发出信号唤醒等待线程。
参数：
sem：信号量地址。
返回值：
成功返回 0，失败返回-1。


int sem_getvalue(sem_t *sem, int *sval);
功能：
获取 sem 标识的信号量的值，保存在 sval 中。
参数：
sem：信号量地址。
sval：保存信号量值的地址。
返回值：
成功返回 0，失败返回-1。

int sem_destroy(sem_t *sem);
功能：
删除 sem 标识的信号量。
参数：
sem：信号量地址。
返回值：
成功返回 0，失败返回-
*/

// 通过信号量实现互斥操作

// 第一步：创建一个信号量
sem_t sem;

void printer(char *str)
{
    // 第三步：执行P操作
    // 由于使用信号量实现互斥，信号量的初始值设置为1，则两个线程执行P操作
    // 先执行操作的P操作的线程继续执行，后执行P操作的先阻塞等待
    sem_wait(&sem);
    while (*str)
    {
        putchar(*str);
        fflush(stdout);
        str++;
        sleep(1);
    }

    // 第四步：执行V操作
    sem_post(&sem);
}

void *thread_fun1(void *arg)
{
    char *str1 = "hello";
    printer(str1);
}

void *thread_fun2(void *arg)
{
    char *str2 = "world";
    printer(str2);
}

int main(int argc, char *argv[])
{
    // 第二步：初始化信号量
    sem_init(&sem, 0, 1);

    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread_fun1, NULL);
    pthread_create(&tid2, NULL, thread_fun2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("\n");

    // 第五步：使用完毕后销毁信号量
    sem_destroy(&sem);

    return 0;
}
