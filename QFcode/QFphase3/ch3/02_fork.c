#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    if(pid < 0)
    {
        perror("fail to fork");
        return -1;
    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("parent:pid = %d, ppid = %d\n", getpid(), getpgid(getppid()));
            printf("son pid = %d\n", pid);
            printf("This is a parent process\n");
            sleep(1);
            printf("************************\n");
        }
    }
    else
    {
        while(1)
        {
            printf("son:pid = %d, ppid = %d\n", getpid(), getppid());
            printf("This is a parent process\n");
            sleep(1);
            printf("------------------------\n");
        }
    }

    return 0;
}