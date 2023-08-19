#include "001StdThread.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem[3];
void *Print1(void *arg)
{
    while (1)
    {
        // p
        sem_wait(&sem[0]);
        printf("A\n");
        sleep(1);
        // v
        sem_post(&sem[1]);
    }
}

void *Print2(void *arg)
{
    while (1)
    {
        // p
        sem_wait(&sem[1]);
        printf("B\n");
        sleep(1);
        // v
        sem_post(&sem[2]);
    }
}

void *Print3(void *arg)
{
    while (1)
    {
        // p
        sem_wait(&sem[2]);
        printf("C\n");
        sleep(1);
        // v
        sem_post(&sem[0]);
    }
}

int main(int argc, char *argv[])
{
    sem_init(&sem[0], 0, 1);
    sem_init(&sem[1], 0, 0);
    sem_init(&sem[2], 0, 0);

    Thread *t1 = InitThread(Print1, NULL);
    Thread *t2 = InitThread(Print2, NULL);
    Thread *t3 = InitThread(Print3, NULL);

    JoinThread(t1);
    JoinThread(t2);
    JoinThread(t3);

    for (int i = 0; i < 3; i++)
    {
        sem_destroy(&sem[i]);
    }
    return 0;
}