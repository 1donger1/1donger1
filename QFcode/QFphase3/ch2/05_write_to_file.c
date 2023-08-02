#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


//向文件写入数据
int main(int argc, char *argv[])
{
    int fd;
    fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd == -1)
    {
        perror("fail to open");
        return -1;
    }

    ssize_t bytes;
    if((bytes = write(fd, "hello world\n", 12)) == -1)
    {
        perror("fail to write");
        return -1;
    }

    printf("bytes = %ld\n", bytes);

    write(fd, "nihao beijing", 5);

    close(fd);

    return 0;
}