#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char str[] = "www.runoob.com";
    int i = 0;
    while(str[i] != '\0')
    {
        i++;
    }
    printf("%d\n", i);

    return 0;
}