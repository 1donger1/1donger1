#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
线程被取消后，该线程并不是马上终止，默认情况下线程执行到消点时才能被终止。编程时可以通过
pthread_setcanceltype 函数设置线程是否可以立即被取消。
pthread_setcanceltype(int type, int *oldtype);
type：
PTHREAD_CANCEL_ASYNCHRONOUS：立即取消、
PTHREAD_CANCEL_DEFERRED：不立即被取消
oldtype：
保存调用线程原来的可取消类型的内存地址。
*/

void *pthread_fun(void *arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    //设置线程取消的类型
    //设置为立即取消
    // pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    //设置为不立即取消
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    while (1)
    {
        printf("子线程正在运行\n");
        sleep(1);
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