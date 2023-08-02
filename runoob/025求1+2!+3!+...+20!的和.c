#include <stdio.h>
#include <stdlib.h>

// 求1+2!+3!+...+20!的和。

int main(int argc, char *argv[])
{
    int i;
    long double sum, mix;
    sum = 0, mix = 1;
    for (i = 1; i <= 20; i++)
    {
        mix = mix * i;
        sum = sum + mix;
    }

    printf("Lf\n", sum);

    return 0;
}