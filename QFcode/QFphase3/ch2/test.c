#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        perror("fait to argc");
        return -1;
    }

    printf("argc = %d\n", argc);
    printf("argv[1] = %s\n", argv[1]);
    return 0;
}