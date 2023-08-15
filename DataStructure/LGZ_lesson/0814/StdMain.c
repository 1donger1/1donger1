#include "StdFIFO.h"
#include "SystemHead.h"

int main(int argc, char *argv[])
{
    FIFO *f = InitFIFO("StdFIFOTest");

    pid_t pid = fork();
    if (pid == 0)
    {
        OpenFIFO(f, WriteOnly);
        WriteToFIFO(f, "Donger", 6);
    }
    else
    {
        OpenFIFO(f, ReadOnly);
        char temp[10] = {0};
        ReadFromFIFO(f, temp, 10);
        printf("%s\n", temp);
    }
    ClearFIFO(f);
    return 0;
}