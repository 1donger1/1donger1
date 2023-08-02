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
        exit(1);
    }
    else if (pid == 0)
    {
        int i = 0;
        for (i = 0; i < 5; i++)
        {
            printf("This is a son process\n");
            sleep(1);
        }

        exit(0);
    }
    else
    {
        int status = 0;
        waitpid(pid, NULL, 0);

        printf("This is a father process\n");
    }

    return 0;
}

/**
 * pid：要等待的子进程的PID。有以下几种取值：
    > 0：等待具有指定PID的子进程结束。
    -1：等待任何一个子进程结束，相当于wait函数。
    0：等待与调用进程属于同一进程组的任何子进程结束。
    < -1：等待任何一个进程组ID等于pid的子进程。
status：用于存储子进程的退出状态信息。通过指针传递，该参数可以获取子进程的退出状态或导致子进程终止的原因。
options：用于指定等待子进程的行为选项。
WNOHANG：如果没有终止的子进程，则立即返回，而不是阻塞等待。
WUNTRACED：如果子进程处于暂停状态而不是终止状态，则返回。
WCONTINUED：如果子进程被暂停后恢复了运行，则返回。
返回值是子进程的PID，有以下几种情况：

如果成功等待到一个子进程结束，返回结束的子进程PID。
如果使用WNOHANG选项并且没有已终止的子进程，返回0。
如果调用出错，返回-1，并设置errno来指示错误的原因。
注意：waitpid函数调用时会阻塞父进程，直到满足等待条件的子进程结束。
*/