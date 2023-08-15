#include "SystemHead.h"
#define FIFO "MyFIFO"
#define FIFO2 "MyFIFO2"

int main(int argc, char *argv[])
{
    mkfifo(FIFO, S_IRUSR | S_IWUSR);
    int fd_first = open(FIFO, O_RDONLY);

    if (fd_first < 0)
    {
        perror("open : ");
        exit(1);
    }
    int fd_second = open(FIFO2, O_WRONLY);

    if (fd_second < 0)
    {
        perror("open : ");
        exit(1);
    }
    while (1)
    {
        char temp[100] = {0};
        read(fd_first, temp, sizeof(temp));
        printf("read from 1:%s\n", temp);

        printf("Please input message to 1:");
        memset(temp, 0, 100);
        scanf("%[^\n]", temp);
        while (getchar() != '\n')
            ;
        write(fd_second, temp, strlen(temp));
    }

    close(fd_first);
    close(fd_second);
    return 0;
}