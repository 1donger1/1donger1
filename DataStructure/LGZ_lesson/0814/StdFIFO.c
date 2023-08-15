#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <fcntl.h>

#include "StdFIFO.h"

#define true 1
#define false 0

struct StdFIFO
{
    char Path[PATH_SIZE];
    int fd;
    Mode mode;
};


FIFO *InitFIFO(const char *path)
{
    FIFO *f = (FIFO *)malloc(sizeof(FIFO));
    if(f == NULL)
    {
        printf("InitFIFO malloc fail!\n");
        return NULL;
    }
    int ret = mkfifo(path, S_IRUSR | S_IWUSR);
    if (ret == -1)
    {
        printf("the FIFO is exist or you have not enough permisson!\n");
    }
    strcpy(f->Path, path);
    return f;
}

int OpenFIFO(FIFO *f, Mode mode)
{
    if (f == NULL)
    {
        return false;
    }
    if (mode == ReadOnly)
    {
        f->fd = open(f->Path, O_RDONLY);
        if (f->fd < 0)
        {
            perror("fail to open!\n");
            return false;
        }
    }
    else if (mode == WriteOnly)
    {
        f->fd = open(f->Path, O_WRONLY);
        if (f->fd < 0)
        {
            perror("fail to open!\n");
            return false;
        }
    }
    f->mode = mode;
    return true;
}

void WriteToFIFO(FIFO *f, void *buff, size_t size)
{
    if (f == NULL)
    {
        return;
    }
    if (f->mode == ReadOnly)
    {
        printf("You cannot write to FIFO, your open mode is ReadOnly!\n");
        return;
    }
    if (write(f->fd, buff, size) <= 0)
    {
        printf("Write number is invalid!\n");
        return;
    }
}

void ReadFromFIFO(FIFO *f, void *buff, size_t size)
{
    if (f == NULL)
    {
        return;
    }
    if (f->mode == WriteOnly)
    {
        printf("You cannot read from FIFO, your open mode is WriteOnly!\n");
        return;
    }
    if (read(f->fd, buff, size) <= 0)
    {
        printf("Read number is invalid!\n");
        return;
    }
}

void ClearFIFO(FIFO *f)
{
    close(f->fd);
    char RMStr[PATH_SIZE * 2] = {0};
    sprintf(RMStr, "rm -f %s", f->Path);
    // printf("Rmstr %s\n", RMStr);
    system(RMStr);

    free(f);
    f = NULL;
}

void SetBlock(FIFO *f, int IsBlock)
{
    if(f == NULL)
    {
        return;
    }
    if (IsBlock == true)
    {
        fcntl(f->fd, F_SETFL, 0);
    }
    else
    {
        fcntl(f->fd, F_SETFL, O_NONBLOCK);
    }
}
