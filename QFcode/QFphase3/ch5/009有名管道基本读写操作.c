#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFONAME "009-file"

int main(int argc, char *argv[])
{
    // 通过mikfifo函数创建有名管道
    if ((mkfifo(FIFONAME, 0664)) == -1)
    {
        if (errno != EEXIST)
        {
            perror("fail to mikfifo\n");
            exit(1);
        }
    }

    // 对有名管道进行操作
    // 管道后写入的数据会保存在之前写入数据的后面，不会替换
    // 如果管道中没有数据了，读操作会阻塞line52
    int fd;
    if ((fd = open(FIFONAME, O_RDWR)) == -1)
    {
        perror("fail to open\n");
        exit(1);
    }

    // 通过write函数向管道写入数据
    if ((write(fd, "hello world", strlen("hello world"))) == -1)
    {
        perror("fail to write\n");
        exit(1);
    }

    write(fd, "nihao nanjing", strlen("nihao nanjing"));

    // 通过read函数读取管道中的数据
    char buf[32] = "";
    if (read(fd, buf, sizeof(buf)) == -1)
    {
        perror("fail to read\n");
        exit(1);
    }
    printf("buf = %s\n", buf);

    // 阻塞
    if (read(fd, buf, sizeof(buf)) == -1)
    {
        perror("fail to read\n");
        exit(1);
    }
    printf("buf = %s\n", buf);

    close(fd);

    return 0;
}