#include "head.h"

int main(int argc, char *argv[])
{
    int x = 2023;
    int y = 1999;

    printf("%d + %d = %d\n", x, y, sum(x, y));
    printf("%d - %d = %d\n", x, y, sub(x, y));

    return 0;
}
