#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
#include <pthread.h>
void pthread_exit(void *retval);
功能：
退出调用线程。
参数:
retval：存储线程退出状态的指针。
这个值可以被调用pthread_join函数接收到
返回值:
无
*/

void *thread_fun()
{
    printf("子线程正在运行\n");

    static char buf[] = "This thread has quited";

    int i;
    for (i = 0; i < 10; i++)
    {
        if(i == 5)
        {
            pthread_exit(buf);
        }

        printf("****************************\n");
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    printf("主控线程正在执行\n");

    pthread_t thread;

    if(pthread_create(&thread, NULL, thread_fun, NULL) != 0)
    {
        perror("fail to pthread");
        exit(1);
    }

    char *str;
    pthread_join(thread, (void **)&str);
    printf("主线程打印str = %s\n", str);

    printf("进程要退出了\n");

    return 0;
}