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
#if 0
    else if (pid == 0)
    {
        char buf[20] = "hello world";
        printf("child process write to parent!\n");
        write(fd[1], buf, strlen(buf));
    }
    else
    {
        char ReadBuff[20] = "";
        read(fd[0], ReadBuff, sizeof(ReadBuff));//read是阻塞函数
        printf("parent process read from child process:%s\n", ReadBuff);
    }
#endif
    else if (pid == 0)//child
    {
        while (1)
        {
            char Buff[100] = "";
            read(fd_first[0], Buff, sizeof(Buff)); // read是阻塞函数
            // printf(" read from parent process:%s\n", Buff);
            printf(" 子进程fd_first[0]读取内容:%s\n", Buff);

            memset(Buff, 0, 100);
            // printf("Please input message to parent:");
            printf("子进程向父进程发消息:");
            scanf("%[^\n]", Buff);
            while(getchar()!= '\n')
                ;
            write(fd_second[1], Buff, strlen(Buff));
        }
    }
    else
    {
        while (1)
        {
            char buff[100] = "hello world";
            // printf("Please input message to child:");
            printf("父进程向子进程发消息:");
            scanf("%[^\n]", buff);
            while (getchar() != '\n')
                ;
            write(fd_first[1], buff, strlen(buff));

            memset(buff, 0, 100);
            read(fd_second[0], buff, sizeof(buff));
            // printf("read from child process:%s\n", buff);
            printf("父进程fd_second[0]从子进程读内容:%s\n", buff);
        }
    }

    return 0;
}