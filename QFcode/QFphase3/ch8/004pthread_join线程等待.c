#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
int pthread_join(pthread_t thread, void **retval);
功能：
等待子线程结束，并回收子线程资源。
参数：
thread：被等待的线程号。
retval：用来存储线程退出状态的指针的地址。
返回值：
成功返回 0，失败返回非 0。
*/

void* thread_fun(void *arg)
{
    static int num = 666;
    printf("子线程正在运行\n");

    sleep(3);

    printf("子线程要退出了\n");

    //子线程如果要返回退出状态，可以通过返回值或通过pthread_exit函数
    return (void *)&num;
}

int main(int argc, char *argv[])
{
    printf("主控线程正在执行\n");

    pthread_t thread;

    if(pthread_create(&thread, NULL, thread_fun, NULL) != 0)
    {
        perror("fail to pthread_create");
    }

    int *num;
    if(pthread_join(thread, (void **)&num) != 0)
    {
        perror("fail to pthread_join");
        exit(1);
    }

    printf("ret_val = %d\n", *num);
    printf("进程要退出了\n");

    return 0;
}