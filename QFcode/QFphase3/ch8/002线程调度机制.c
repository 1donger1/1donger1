#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *pthread_fun1(void *arg)
{
    printf("子线程1正在运行\n");
    sleep(1);
    printf("*************************************\n");
}

void *pthread_fun2(void *arg)
{
    printf("子线程2正在运行\n");
    sleep(1);
    printf("-------------------------------------\n");
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, pthread_fun1, NULL) == -1)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, pthread_fun2, NULL) == -1)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    while(1)
        ;

    return 0;
}