#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (i = 0; i < 8; i++)
        {
            if ((i + j) % 2 == 0)
            {
                printf("%c%c", 219, 219);
            }
            else
            {
                printf("\n");
            }
        }
    }

    return 0;
}
