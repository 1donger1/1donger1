#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
// void test1(int a[])
// {
//     printf("test1:%ld\n", sizeof(a)/sizeof(int));
// }
// void test2(int *a)
// {
//     printf("test2:%ld\n", sizeof(a) / sizeof(int));
// }
// void test3(int (*p)[])
// {
//     printf("test3:%ld\n", sizeof(p) / sizeof(int));
// }

int main(int argc, char *argv[])
{
    int a[N];
    initnum(a, N);

    // BubbleSort(a, N);
    // Bubblesort(a, N);
    // Bubblesort2(a, N);

    // choosesort(a, N);

    // insertsort(a, N);

    // shellsort(a, N);

    // QuickSort(a, 0, N - 1);
    quicksort(a, 0, N - 1);
    printf("快速排序后:");
    print(a, N);

    // test1(a);
    // test2(a);
    // test3(&a);
    return 0;
}
