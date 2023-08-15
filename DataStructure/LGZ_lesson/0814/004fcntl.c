#include "SystemHead.h"

int main(int argc, char *argv[])
{
    // 创建管道
    int fd_first[2];
    int fd_second[2];
    if (pipe(fd_first) == -1)
    {
        perror("fail to pipe!\n");
        exit(1);
    }
    if (pipe(fd_second) == -1)
    {
        perror("fail to pipe!\n");
        exit(1);
    }

    // 创建进程
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fail to fork!\n");
        exit(1);
    }
    else if (pid == 0) // child
    {
        int fd_stdin = fileno(stdin);
        fcntl(fd_stdin, F_SETFL, O_NONBLOCK);
        while (1)
        {
            char temp[100] = {0};
            scanf("%s", temp);
            printf("Im child process! temp:%s\n", temp);
            sleep(1);
        }
    }
    else
    {
        fcntl(fd_first[0], F_SETFL, 0);//代表阻塞
        // fcntl(fd_first[0], F_SETFL, O_NONBLOCK);//不阻塞
        while (1)
        {
            char temp[100] = {0};
            printf("Im parent process!\n");
            read(fd_first[0], temp, sizeof(temp));
            printf("read from child:%s\n", temp);
            sleep(3);
        }
    }

    return 0;
}