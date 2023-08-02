#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
设置为阻塞：
fcntl(fd, F_SETFL, 0);
设置为非阻塞：
fcntl(fd, F_SETFL, O_NONBLOCK);
*/

int main(int argc, char *argv[])
{
    char buf[] = "hello world";
    pid_t pid;

    int fd_pipe[2];
    if(pipe(fd_pipe) < 0)
    {
        perror("fail to pipe\n");
        exit(1);
    }

    if ((pid = fork()) < 0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if (pid > 0) // 父进程
    {
        // 将fd_pipe[0]设置为阻塞
        //  fcntl(fd_pipe[0], F_SETFL, 0);

        // 将fd_pipe[0]设置为非阻塞
        fcntl(fd_pipe[0], F_SETFL, O_NONBLOCK);

        while(1)
        {
            memset(buf, 0, sizeof(buf));
            read(fd_pipe[0], buf, sizeof(buf));
            printf("buf = %s\n", buf);
            sleep(1);
        }
    }
    else // 子进程
    {
        while(1)
        {
            sleep(5);
            write(fd_pipe[1], buf, strlen(buf));
        }
    }

    return 0;
}