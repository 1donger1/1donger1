#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


/*
void (*signal(int sig, void (*func)(int)))(int);
typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
功能：当进程中产生某一个信号时，对当前信号进行处理
参数：
sig:指定要处理的信号
handler:理方式
SIG_IGN 当信号产生时，以缺省（忽略）的方式处理
SIG_DFL 当信号产生时，以当前信号默认的方式处理
void handler(int sig)：当信号产生时，通过信号处理函数自定义方式处理，函数名可以随便写，
参数:表示当前的信号
返回值：
    成功：返回函数地址，该地址为此信号上一次注册的信号处理函数的地址
    失败:SIG_ERR
*/

void handler(int sig)
{
    if(sig == SIGINT)
    {
        printf("SIGINT正在处理\n");
    }

    if (sig == SIGQUIT)
    {
        printf("SIGQUIT正在处理\n");
    }

    if(sig == SIGTSTP)
    {
        printf("SIGTSTP正在处理\n");
    }
}

int main(int argc, char *argv[])
{
#if 0
    //以默认的方式处理信号
    if(signal(SIGINT, SIG_DFL) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
    if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
#endif

#if 0
    //以忽略的方式来处理信号
    if (signal(SIGINT, SIG_IGN) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
    if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
#endif

#if 1
    // 以自定义的方式来处理信号
    if (signal(SIGINT, handler) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
    if (signal(SIGQUIT, handler) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
    if (signal(SIGTSTP, handler) == SIG_ERR)
    {
        perror("fail to signal\n");
        exit(1);
    }
#endif

    while(1)
    {
        printf("hello world\n");
        sleep(1);
    }
    return 0;
}