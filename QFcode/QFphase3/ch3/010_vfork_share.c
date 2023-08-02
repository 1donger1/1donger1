#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int a = 10;

int main(int argc, char *argv[])
{
    pid_t pid;
    int b = 9;

    pid = vfork();

    if (pid < 0)
    {
        perror("fail to fork");
        return -1;
    }
    else if (pid == 0)
    {
        a++;
        b++;
        printf("In son process,a = %d, b = %d\n", a, b);
        exit(0);
    }
    else
    {
        printf("In father process,a = %d, b = %d\n", a, b);
    }

    return 0;
}