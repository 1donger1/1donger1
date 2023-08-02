#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    //如果需要实现输出重定向的功能
    //首先像printf函数是操作文件描述符1所对应的文件，默认是操作终端，
    //只要能够把对应标识的文件改变，就可以实现输出重定向
    //所以实现创建好文件对应的文件描述符之后，将1文件描述符关闭，
    //接着通过dup函数复制的新的文件描述符就是1，这样printf函数对1操作，就写到了文件

    int fd_file;
    fd_file = open("06_1file_dup.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    //printf("fd_file = %d\n", fd_file);    //3

    if(fd_file == -1)
    {
        
        perror("fail to open\n");
        exit(1);
    }

    close(1);

    int fd = dup(fd_file);
    write(fd, "write\n", strlen("write\n"));
    printf("hello world\n");//实现输出重定向
    printf("fd = %d\n", fd);

    return 0;
}