#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../MyLibrary/Mysort/Mysort.h"
#define MAX 5

int main()
{
    srand(time(NULL));
    int a[MAX] = {};
    for (int i = 0; i < MAX; i++)
    {
        a[i] = rand() % 20 + 1;
    }
    printf("排序前：");
    for (int i = 0; i < MAX; i++)
    {
        printf("%3d", a[i]);
    }

    BubbleSort(a, MAX, IsBiggr);

    printf("\n");

    printf("排序后:");
    for (int i = 0; i < MAX; i++)
    {
        printf("%3d", a[i]);
    }

    printf("\n");
}