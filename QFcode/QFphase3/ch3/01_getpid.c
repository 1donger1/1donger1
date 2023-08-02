#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("getpid = %d\n", getpid());
    printf("getppid = %d\n", getppid());
    printf("getpgid = %d\n", getpgid(getpid()));

    while (1)
        sleep(3);
    return 0;
}