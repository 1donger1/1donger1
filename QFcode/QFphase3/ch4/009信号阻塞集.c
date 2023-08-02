#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    while(1)
    {
        //将set信号集添加到信号阻塞集中
        sigprocmask(SIG_BLOCK, &set, NULL);
        for (i = 0; i < 5; i++)
        {
            printf("SIGINT signal is blocked\n");
            sleep(1);
        }

        sigprocmask(SIG_UNBLOCK, &set, NULL);
        for (i = 0; i < 5; i++)
        {
            printf("SIGINT signal is unblocked\n");
            sleep(1);
        }
    }


    return 0;
}