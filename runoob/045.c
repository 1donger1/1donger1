#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    register int i;
    int temp = 0;
    for (i = 1; i <= 100; i++)
    {
        temp += i;
    }
    printf("总和为%d\n", temp);

    return 0;
}
