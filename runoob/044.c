#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    // int a = 4, b = 3;
    static int c;
    c = a + b;
    return c;
}

int main(int argc, char *argv[])
{
    int a = 3, b = 4;

    // fun(a, b);
    printf("%d\n", add(a, b));
    return 0;
}