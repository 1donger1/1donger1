#include "002SystemHead.h"

int main(int argc, char *argv[])
{
    key_t key = ftok("./", 10);
    if (key < 0)
    {
        perror("fail to ftok");
        exit(1);
    }

    int shmID = shmget(key, 1024, IPC_CREAT | 0664);
    printf("ipcs-m shmID = %d\n", shmID);

    void *text = shmat(shmID, NULL, 0);

    strcpy((char *)text, "Hello KuGou!");

    if (shmdt(text) != 0)
    {
        perror("shmdt");
    }

    // shmctl(shmID, IPC_RMID, NULL);

    return 0;
}