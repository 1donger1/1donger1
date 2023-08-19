#include "002SystemHead.h"
#include "005SharedMemory.h"

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if (pid == 0)
    {
        ShMemory *m = InitSharedMemory("./", 13, 1024);
        if (m == NULL)
        {
            perror("fail to InitSharedMemory\n");
            exit(1);
        }

        char temp[20] = "Test005,hello!";
        WriteToSharedMemory(m, temp, 20);
    }
    else
    {
        wait(NULL);
        ShMemory *m = InitSharedMemory("./", 13, 1024);
        if (m == NULL)
        {
            perror("fail to InitSharedMemory\n");
            exit(1);
        }

        char temp[20] = {0};
        ReadFromSharedMemory(m, temp, 20);
        printf("Read from :%s\n", temp);

        ClearSharedMemory(m);
    }

    return 0;
}