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
    int fd2;
    fd2 = dup(1);
    printf("new:fd2 = %d\n", fd2);

    fd1 = open("06_2file.txt", O_RDWR | O_CREAT, 0664);

    close(1);

    int fd3 = dup(fd1);
    printf("hello fd3\n");
    printf("fd3 = %d\n", fd3);

    close(1);

    //printf("close(1)后fd3 = %d\n", fd3);//
    int fd4 = dup(fd2);
    printf("hello fd4\n");
    printf("fd4 = %d\n", fd4);

    return 0;
}