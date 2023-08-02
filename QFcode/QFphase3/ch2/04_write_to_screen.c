#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //write

//向终端写入数据
int main(int argc, char *argv[])
{
    if(write(1, "hello world\n", 12) == -1)
    {
        perror("fail to write");
        return -1;
    }

    return 0;
}