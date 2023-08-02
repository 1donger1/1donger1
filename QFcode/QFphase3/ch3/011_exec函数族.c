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
        return -1;
    }
    else if (pid > 0)
    {
        printf("This is a parent process\n");

        wait(NULL);

        printf("The son process quit\n");
    }
    else
    {
        printf("This is a son process\n");
    }

    return 0;
}
/***********************************************/