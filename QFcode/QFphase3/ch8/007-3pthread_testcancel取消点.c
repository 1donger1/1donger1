#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
线程的取消点
线程被取消后，该线程并不是马上终止，默认情况下线程执行到消点时才能被终止。编程时可以通过
pthread_testcancel 函数设置线程的取消点。
void pthread_testcancel(void);
当别的线程取消调用此函数的线程时候，被取消的线程执行到此函数时结束
*/

void *pthread_fun(void *arg)
{
    while (1)
    {
        printf("子线程正在运行\n");
        sleep(1);

        pthread_testcancel();
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, pthread_fun, NULL) != 0)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    // 通过调用pthread_cancel函数取消另一个线程
    sleep(3);
    pthread_cancel(thread);

    pthread_join(thread, NULL);

    return 0;
}