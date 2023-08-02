#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define N 64

// 从文件中读取数据
int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open("file.txt", O_RDONLY | O_CREAT, 0664)) == -1)
    {
        perror("fail to open");
        return -1;
    }

    char buf[N] = "";
    ssize_t bytes;
#if 0
    if((bytes = read(fd, buf, 3)) == -1)
    {
        perror("fail to read");
        return -1;
    }

    printf("buf = [%s]\n", buf);
    printf("bytes = %ld\n", bytes);

    char buf1[N] = "";
    bytes = read(fd, buf1, 3);
    printf("buf = [%s]\n", buf1);
    printf("bytes = %ld\n", bytes);

    char buf2[N] = "";
    bytes = read(fd, buf2, 3);
    printf("buf = [%s]\n", buf2);
    printf("bytes = %ld\n", bytes);
#endif

    while ((bytes = read(fd, buf, 3)) != 0)
    {
        printf("buf = [%s]\n", buf);
        printf("bytes = %ld\n", bytes);
    }

    return 0;
}
