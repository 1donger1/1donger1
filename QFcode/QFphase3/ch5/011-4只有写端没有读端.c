#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (mkfifo("myfifo", 0664))
    {
        if (errno != EEXIST)
        {
            perror("fail to mkfifo\n");
            exit(1);
        }
    }

    // 在一个进程中，只有写端，没有读端
    // 会在open函数的位置阻塞

    printf("************************************\n");

    int fd;
    if ((fd = open("myfifo", O_RDONLY)) == -1)
    {
        perror("fail to open\n");
        exit(1);
    }

    printf("------------------------------------\n");


    while (1)
    {
        write(fd, "hello world", 11);
        printf("666\n");
    }

    return 0;
}