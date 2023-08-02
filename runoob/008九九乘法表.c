#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;
    int result;
    for (i = 1; i <= 9; i++)
    {
        for (j = 1; j <= i; j++)
        {
            result = i * j;
            printf("%d*%d = %-3d ", i, j, result);
        }
        printf("\n");
    }

    return 0;
}