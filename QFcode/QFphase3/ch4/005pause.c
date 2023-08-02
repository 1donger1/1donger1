#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/*
int pause(void);
功能：阻塞等待一个信号的产生
参数：
无
返回值：
当有信号产生时，函数返回‐1
*/

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();
    if(pid < 0)
    {
        perror("fail to fork\n");
        exit(1);
    }

    else if(pid > 0)
    {
        printf("This is parent process\n");

        //使用pause阻塞等待捕捉信号
        pause();
    }
    else
    {
        printf("This is son process\n");

        sleep(3);

        kill(getppid(), SIGINT);
    }

    return 0;
}