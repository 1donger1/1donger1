#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("fail to fork");
    }
    else if (pid == 0)
    {
        pid = getpid();
        printf("son_pid = %d\n", pid);
        int i = 0;
        for (i = 0; i < 5; i++)
        {
            printf("This is a son process\n");
            sleep(1);
        }

        exit(2);
    }
    else
    {
        // wait功能：等待子进程终止，如果子进程终止了，此函数会回收子进程的资源
        // 调用wait函数的进程会挂起。直到它的一个子进程退出或收到一个不能忽视的信号才会被唤醒
        // 若调用函数没有子进程或它的子进程已经结束，该函数立即返回
        // 返回值：成功：子进程的进程号；--失败：-1

        // 参数status:函数返回时，参数status中包含子进程退出的状态信息，
        // 子进程退出信息在一个int中包含了多个字段，可以用宏定义取出每个字段
        int status = 0;
        pid = wait(&status);

        printf("wait->pid = %d\n", pid);

        // WIFEXITED(status)如果子进程是正常终止，取出的字段非零
        if(WIFEXITED(status) != 0)
        {
            // WEXITSTATUS(status)返回子进程的退出状态，在使用此宏之前应先用WIFEXITED判断子进程是否正常退出
            printf("The son process return status:%d\n", WEXITSTATUS(status));
        }

        printf("This is a father process\n");
    }

    return 0;
}