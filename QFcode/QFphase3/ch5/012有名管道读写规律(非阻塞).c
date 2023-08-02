#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;

    if (mkfifo("myfifo", 0664))
    {
        if (errno != EEXIST)
        {
            perror("open fifo\n");
            exit(1);
        }
    }

#if 0
    //如果open标志位设置为非阻塞，并且以只读的方式打开管道文件
    //open函数和read函数都不会阻塞
    fd = open("myfifo", O_RDONLY | O_NONBLOCK);

    if(fd < 0)
    {
        perror("open fifo");
        exit(1);
    }

    while(1)
    {
        char recv[100];

        bzero(recv, sizeof(recv));
        read(fd, recv, sizeof(recv));
        printf("read from my_fifo buf = %s\n", recv);
        sleep(1);
    }
#endif

    char send[100] = "How I love you!";

    //fd = open("myfifo", O_WRONLY | O_NONBLOCK);
    fd = open("myfifo", O_RDWR | O_NONBLOCK);

    if(fd < 0)
    {
        perror("open fifo");
        exit(1);
    }

    write(fd, send, strlen(send));

    char recv[100];
    read(fd, recv, sizeof(recv));
    printf("read from myfifo buf = %s\n", recv);

    return 0;
}