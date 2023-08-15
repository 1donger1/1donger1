#include "SystemHead.h"
#define FIFO "MyFIFO"
#define FIFO2 "MyFIFO2"
int main(int argc, char *argv[])
{
    mkfifo(FIFO, S_IRUSR | S_IWUSR);
    mkfifo(FIFO2, S_IRUSR | S_IWUSR);
    // open函数打开管道是阻塞函数，当读写端同时打开才继续执行
    int fd_first = open(FIFO, O_WRONLY);

    if (fd_first < 0)
    {
        perror("open : ");
        exit(1);
    }
    int fd_second = open(FIFO2, O_RDONLY);

    if (fd_second < 0)
    {
        perror("open : ");
        exit(1);
    }
    while (1)
    {
        char temp[100] = "";
        printf("Please input message to 2:");

        scanf("%[^\n]", temp);
        while (getchar() != '\n')
            ;
        write(fd_first, temp, strlen(temp));

        memset(temp, 0, 100);
        read(fd_second, temp, sizeof(temp));
        printf("read from 2 : %s\n", temp);
    }
    close(fd_first);
    close(fd_second);
    return 0;
}