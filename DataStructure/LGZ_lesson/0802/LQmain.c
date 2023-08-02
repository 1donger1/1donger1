#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

int main(int argc, char *argv[])
{
    LQueue queue;
    InitLQueue(&queue);

    for (int i = 0; i < 10; i++)
    {
        QPush(&queue, i + 1);
    }

    Trave(&queue.queue);

    while(IsQEmpty(&queue) == false)
    {
        printf("%d ", *Pop(&queue));
    }
    printf("\n");

    return 0;
}