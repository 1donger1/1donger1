#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
int pthread_cancel(pthread_t thread);
功能：
取消线程。
参数：
thread:目标线程 ID。
返回值：
成功返回 0，失败返回出错编号。
pthread_cancel 函数的实质是发信号给目标线程 thread，使目标线程退出。
此函数只是发送终止信号给目标线程，不会等待取消目标线程执行完才返回。
然而发送成功并不意味着目标线程一定就会终止，线程被取消时，线程的取消属性会决定线程能否被取消以
及何时被取消。
*/

void * pthread_fun(void * arg)
{
    while(1)
    {
        printf("子线程正在运行\n");
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread;

    if(pthread_create(&thread, NULL, pthread_fun, NULL) != 0)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    //通过调用pthread_cancel函数取消另一个线程
    sleep(3);
    pthread_cancel(thread);

    pthread_join(thread, NULL);

    return 0;
}