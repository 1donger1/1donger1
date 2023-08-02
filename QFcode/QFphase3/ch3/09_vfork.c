#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    pid_t pid;
    pid = vfork();

    if (pid < 0)
    {
        perror("fail to fork");
        return -1;
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
        while (1)
        {
            printf("This is a parent process\n");
            sleep(1);
        }
    }

    return 0;
}