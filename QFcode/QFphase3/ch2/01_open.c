#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

//用open创建文件，并通过函数调用出错信息
int main(int argc, char const * argv[])
{
    int fd;
    //fd = open("01file.txt", O_RDONLY | O_CREAT, 0664);
    fd = open("01file.txt", O_RDONLY );//errno = 2

    if(fd = -1)
    {
        perror("fail to open");

        printf("errno = %d\n", errno);
        return -1;
    }

    printf("fd = %d\n", fd);

    return 0;
}