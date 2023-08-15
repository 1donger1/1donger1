#include "SystemHead.h"
#include <stdio.h>
#include <stdlib.h>


// int global_num = 0;
int main(int argc, char *argv[])
{
    int num = 0;
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fail to fork");
    }

    if (pid == 0) // child
    {
        sleep(3);

        num++;
        // global_num++;
        printf("child process\n");
        // printf("child process num  :%d,address :%p\n", num, &num);
        // printf("child process global_num :%d,address :%p\n", global_num, &global_num);
       
        // exit(2);
    }
    else
    {
        int status = 0;
        printf("parent process\n");
        // printf("parent process num  :%d,address :%p\n", num, &num);
        // printf("parent process global_num :%d,address :%p\n", global_num, &global_num);

        // wait(&status);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) != 0)
        {
            printf("child exit status is %d\n", WEXITSTATUS(status));//获取高8位的
        }
    }

    // printf("%d\n", ++num);

    return 0;
}