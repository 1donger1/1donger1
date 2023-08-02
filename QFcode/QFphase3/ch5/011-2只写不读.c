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

    //读写端都存在，只写不读
    //当有名管道的缓冲区写满后，write函数会发生阻塞
    //默认有名管道的缓冲区去为64KB

    int fd;
    if((fd = open("myfifo", O_RDWR)) == -1)
    {
        perror("fail to open\n");
        exit(1);
    }

    int num = 0;
    while(1)
    {
        write(fd, "V", 1024);
        num++;
        printf("num = %d\n", num);
    }

    return 0;
}