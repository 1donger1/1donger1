#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

/*
int kill(pid_t, int sig);
功能：给指定的进程或者进程组发送信号 
参数： 
pid： 
    pid > 0 : 将信号传送给进程ID为pid的进程。 
    pid = 0 : 将信号传送给当前进程所在进程组中的所有进程。 
    pid =‐1 : 将信号传送给系统内所有的进程，除了init进程 
    pid <‐1 : 将信号传给指定进程组的所有进程。这个进程组号等于pid的绝对值。 
sig：指定的信号 
返回值： 
    成功：0 
    失败：‐1
*/

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    if(pid < 0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("This is parent process\n");
            sleep(1);
        }
    }
    else
    {
        printf("This is son process\n");
        sleep(3);

        kill(getppid(), SIGINT);
    }

    return 0;
}