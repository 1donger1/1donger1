#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

/*
 int dup2(int oldfd, int newfd)
 功能：复制一份打开的文件描述符oldfd，
    并分配新的文件描述符newfd，newfd也标识oldfd所标识的文件。
 注意：
 newfd是小于文件描述符最大允许值的非负整数，
 如果newfd是一个已经打开的文件描述符，则首先关闭该文件，然后再复制。
 参数：
 oldfd：要复制的文件描述符
 newfd：分配的新的文件描述符
 返回值：
 成功：返回newfd
 失败：返回‐1，错误代码存于errno中
*/

int main(int argc, char *argv[])
{
    int fd1;
    int fd2;

    fd1 = open("07-1dup2_file.txt", O_WRONLY | O_CREAT, 0664);
    if(fd1 < 0)
    {
        perror("fail to open\n");
        exit(1);
    }

    // 首先关闭1文件描述符，然后将fd1复制给1，意味着1和fd1都标识07-1dup2_file.txt文件，返回值跟1一样
    fd2 = dup2(fd1, 1);
    printf("hello donger\n");
    printf("fd2 = %d\n", fd2);

    return 0;
}