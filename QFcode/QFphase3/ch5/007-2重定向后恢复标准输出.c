#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1;

    // 如果要使用dup2,则需要事先给第二个参数对应的变量赋一个初始值
    int fd2 = 3;
    dup2(1, fd2); // 将1复制一份为fd2,所以fd2标识的是标准输出
    printf("fd2 = %d\n", fd2);

    fd1 = open("07-2file.txt", O_RDWR | O_CREAT, 0664);

    // 输出重定向：关闭文件描述符1，将fd1复制一份为1，所以1此时标识的是07-2file.txt
    dup2(fd1, 1);
    printf("hello apple\n");

    // 再次实现标准输出：关闭文件描述符1，将fd2复制一份为1，所以1此时表示标准输出
    dup2(fd2, 1);
    printf("hello orange\n");

    return 0;
}