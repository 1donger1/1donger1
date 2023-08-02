#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

/*
 int dup(int oldfd);
功能：复制oldfd文件描述符，并分配一个新的文件描述符，
新的文件描述符是调用进程文件描述符表中最小可用的文件描述符。
参数：
要复制的文件描述符oldfd。
返回值：
成功：新文件描述符。
失败：返回－1，错误代码存于errno中。
*/

int main(int argc, char *argv[])
{
    // 通过dup函数复制一个文件描述符
    int fd;

    // dup执行后给返回值文件描述符分配的值时文件描述符表中最小可用的文件描述符
    if ((fd = dup(1)) == -1)
    {
        perror("fail to dup");
        exit(1);
    }
    else
    {
        printf("fd = %d\n", fd);
    }

    write(fd, "nihao beijing\n", strlen("nihao beijing\n"));

    return 0;
}