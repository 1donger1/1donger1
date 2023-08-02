#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
int pthread_create(pthread_t *thread,const pthread_attr_t *attr,
void *(*start_routine)(void *),void *arg);
功能：
创建一个线程。
参数：
thread：线程标识符地址。
attr：线程属性结构体地址。
start_routine：线程函数的入口地址。
arg：传给线程函数的参数。
返回值：
成功：返回 0
失败：返回非 0
*/

void *thread_fun(void *arg)
{
    printf("子线程正在执行:\n");
}

int main(int argc, char *argv[])
{
    printf("主控线程正在执行:\n");

    pthread_t thread;

    if (pthread_create(&thread, NULL, thread_fun, NULL) != 0)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    // 由于进程结束后，进程中所有的线程都会强制退出，所以现阶段不要让进程退出
    while (1)
        ;

    return 0;
}