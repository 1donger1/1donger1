#include <stdio.h>
#include <stdlib.h>

// 练习函数调用。

void print()
{
    int i;
    for (i = 0; i < 3;i++)
    {
        printf("hello world\n");
    }
    return;
}

int main(int argc, char *argv[])
{
    print();

    return 0;
}
