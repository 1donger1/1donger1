#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
线程的取消状态
在 Linux 系统下，线程默认可以被取消。
编程时可以通过 pthread_setcancelstate 函数设置线程是否可以被取消。
pthread_setcancelstate(int state,int *old_state);
state：
PTHREAD_CANCEL_DISABLE：不可以被取消
PTHREAD_CANCEL_ENABLE：可以被取消。
old_state：
保存调用线程原来的可取消状态的内存地址。
*/

void *pthread_fun(void *arg)
{
    // 通过pthread_setcancelstate设置取消状态
    // 设置可以取消
    // pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    // 设置不可取消
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

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