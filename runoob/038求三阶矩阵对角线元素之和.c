#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int main(int argc, char *argv[])
{
    int i, j, sum = 0;
    int a[N][N];
    srand(time(NULL));

    printf("该数组为:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            a[i][j] = rand() % 100;
            printf("%-3d", a[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < N; i++)
    {
        sum += a[i][i];
    }
    printf("对角线之和为:%d\n", sum);

    return 0;
}