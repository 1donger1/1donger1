#include "002SystemHead.h"

void handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("get SIGINT!\n");
    }
    else if (signal == SIGQUIT)
    {
        printf("get SIGQUIT\n");
    }
    else if (signal == SIGTSTP)
    {
        printf("get SIGTSTP\n");
    }
}

int main(int argc, char *argv[])
{
    // pid_t pid;
    // pid = fork();
    // if (pid < 0)
    // {
    //     perror("fork:");
    //     return -1;
    // }
    // else if (pid > 0)
    // {
    //     sleep(3);
    //     printf("send signal to child!\n");
    //     kill(pid, SIGINT);
    //     wait(NULL);
    // }
    // else
    // {
    //     while (1)
    //     {
    //         sleep(1);
    //         printf("Im child process\n");
    //         // pause();
    //     }
    // }

    // alarm(5);
    // while (1)
    // {
    //     printf("Im running!\n");
    //     sleep(1);
    // }

    // int num = 0;
    // while (1)
    // {
    //     printf("Im running!\n");
    //     sleep(1);
    //     num++;
    //     if (num == 5)
    //     {
    //         abort();
    //     }
    // }

    // signal(SIGINT, handler);
    // signal(SIGINT, SIG_IGN);//忽略ignore ctrl c
    signal(SIGINT, SIG_DFL); // 以默认方式处理
    signal(SIGQUIT, handler);
    signal(SIGTSTP, handler);

    while (1)
    {
        printf("Im running\n");
        sleep(2);
    }

    return 0;
}