#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int num = 100;

void *pthread_fun1(void *arg)
{
    printf("子线程1:num = %d\n", num);
    num++;

    int n = *(int *)arg;
    printf("1 n = %d\n", n);
    *(int *)arg = 111;
}

void *pthread_fun2(void *arg)
{
    sleep(1);
    printf("子线程2:num = %d\n", num);

    int n = *(int *)arg;
    printf("2 n = %d\n", n);
}

int main(int argc, char *argv[])
{
    int a = 666;
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, pthread_fun1, (void *)&a) == -1)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, pthread_fun2, (void *)&a) == -1)
    {
        perror("fail to pthread_create");
        exit(1);
    }

    while (1)
        ;
    return 0;
}