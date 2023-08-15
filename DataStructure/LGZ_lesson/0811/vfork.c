#include "SystemHead.h"
// int global_num = 0;
int main(int argc, char *argv[])
{
    int num = 0;
    pid_t pid = vfork();

    if (pid < 0)
    {
        perror("fail to fork");
    }

    if (pid == 0) // child
    {
        num++;
        printf("child process\n");
        printf("child process num: %d, address: %p\n", num, &num);
        sleep(3);
        exit(2);
    }
    else
    {
        printf("parent process\n");
        printf("parent process num: %d, address: %p\n", num, &num);
    }


    return 0;
}