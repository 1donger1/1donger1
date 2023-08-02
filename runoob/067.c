#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

void fun(int *a)
{
    int max = 0;
    int min = 0;

    // 数组作为函数参数传递时，会退化为指针，
    // 所以在fun函数中的sizeof(a)实际上只是指针的大小，而不是数组的大小。
    //  for (int i = 1; i < sizeof(a)/sizeof(int); i++)
    for (int i = 1; i < MAX; i++)
    {
        if (a[max] < a[i])
        {
            max = i;
        }

        if (a[min] > a[i])
        {
            min = i;
        }
    }
    int temp1, temp2;
    temp1 = a[0];
    a[0] = a[max];
    a[max] = temp1;

    temp2 = a[MAX - 1];
    a[MAX - 1] = a[min];
    a[min] = temp2;
    printf("交换后数组为:");
    for (int i = 0; i < MAX; i++)
    {
        printf("%3d", a[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int a[MAX] = {};
    for (int i = 0; i < MAX; i++)
    {
        a[i] = rand() % 20 + 1;
    }
    printf("原数组为:");
    for (int i = 0; i < MAX; i++)
    {
        printf("%3d", a[i]);
    }
    printf("\n");
    fun(a);

    return 0;
}