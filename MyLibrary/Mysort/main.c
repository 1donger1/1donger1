// #include <stdio.h>
#include "Mysort.h"

int main()
{
    int a[] = {5, 8, 3, 1, 9, 2};
    InsertSort(a, ArrayLen(a));

    for (int i = 0; i < ArrayLen(a); i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}