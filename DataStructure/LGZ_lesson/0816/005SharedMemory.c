#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/shm.h>

#include "005SharedMemory.h"

struct SharedMemory
{
    key_t key;
    int shmID;
    size_t size;
};

ShMemory *InitSharedMemory(const char *path, int pro_id, size_t size)
{
    ShMemory *m = (ShMemory *)malloc((sizeof(ShMemory)));
    if (m == NULL)
    {
        printf("InitSharedMemory malloc fail!\n");
        return NULL;
    }

    m->key = ftok(path, pro_id);
    if (m->key < 0)
    {
        perror("fail to InitSharedMemory ftok!\n");
        free(m);
        return NULL;
    }

    m->size = size;
    m->shmID = shmget(m->key, m->size, IPC_CREAT | 0664);
    if(m->shmID < 0)
    {
        perror("fail to InitSharedMemory shmget!\n");
        free(m);
        return NULL;
    }
    return m;
}

void ClearSharedMemory(ShMemory *m)
{
   if( shmctl(m->shmID, IPC_RMID, NULL) != 0)
   {
        perror("fail to ClearSharedMemory shmctl");
        return;
   }
   free(m);
}

void ReadFromSharedMemory(ShMemory *m, void *ptr, size_t size)
{
    if(m->size < size)
    {
        printf("Rsharedmemory size is %ld, your size is bigger!\n", m->size);
        return;
    }

    void *text = shmat(m->shmID, NULL, SHM_RDONLY);

    if(text == NULL)
    {
        perror("ReadFromSharedMemory shmat");
        return;
    }

    memcpy(ptr, text, size);

    // if(shmdt(m->shmID) != 0)
    if(shmdt(text) != 0)
    {
        perror("ReadFromSharedMemory shmdt");
        return;
    }
}

void WriteToSharedMemory(ShMemory *m, void *ptr, size_t size)
{
    if (m->size < size)
    {
        printf("Wsharedmemory size is %ld, your size is bigger!\n", m->size);
        return;
    }

    void *text = shmat(m->shmID, NULL, 0);

    if (text == NULL)
    {
        perror("WriteFromSharedMemory shmat");
        return;
    }

    memcpy(text, ptr, size);

    if (shmdt(text) != 0)
    {
        perror("WriteFromSharedMemory shmdt");
        return;
    }
}
