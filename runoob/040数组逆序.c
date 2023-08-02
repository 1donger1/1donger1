#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

int main(int argc, char *argv[])
{
    int i;
    int a[N];
    srand(time(NULL));

    printf("原数组为:\n");
    for (i = 0; i < N; i++)
    {
        a[i] = rand() % 100;
        printf("%-4d", a[i]);
    }
    printf("\n");

    int *begin = a, *end = a + N - 1;
    int temp;
    while (begin < end)
    {
        temp = *begin;
        *begin = *end;
        *end = temp;
        begin++;
        end--;
    }

    printf("逆序后数组为:\n");
    for (i = 0; i < N; i++)
    {
        printf("%-4d", a[i]);
    }
    printf("\n");

    return 0;
}
