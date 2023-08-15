#include "SystemHead.h"

void Func()
{
    printf("malloc free!\n");
}

int main(int argc, char *argv[])
{
    atexit(Func);

    printf("main run\n");

    sleep(1);

    return 0;
}