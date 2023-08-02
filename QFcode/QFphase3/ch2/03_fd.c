#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// 文件描述符相关问题

int main(int argc, char *argv[])
{
    // 测试1：一个进程创建的文件描述符个数
    // 一个程序运行的时候最多可以创建1024个文件描述符
#if 1
    int fd;
    while (1)
    {
        fd = open("file.txt", O_RDONLY | O_CREAT, 0664);

        if (fd == -1)
        {
            perror("fail to open");
            return -1;
        }

        printf("fd = %d\n", fd);
    }
#endif

#if 0
    int fd1, fd2, fd3, fd4;
    fd1 = open("file.txt", O_RDONLY | O_CREAT, 0664);
    fd2 = open("file.txt", O_RDONLY | O_CREAT, 0664);
    fd3 = open("file.txt", O_RDONLY | O_CREAT, 0664);
    fd4 = open("file.txt", O_RDONLY | O_CREAT, 0664);

    printf("fd1 = %d\n", fd1);
    printf("fd2 = %d\n", fd2);
    printf("fd3 = %d\n", fd3);
    printf("fd4 = %d\n", fd4);

    close(fd2);

    int fd5, fd6;
    fd5 = open("file.txt", O_RDONLY | O_CREAT, 0664);
    fd6 = open("file.txt", O_RDONLY | O_CREAT, 0664);

    printf("fd5 = %d\n", fd5);
    printf("fd6 = %d\n", fd6);
#endif
    return 0;
}

