#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fun(int *a, int n, int m)
{
    int b[n];
    for (int i = 0; i < n; i++)
    {
        b[i] = 0;
    }

    int i, j = 0;
    for (i = m; i < n; i++)
    {
        b[j++] = a[i];
    }

    for (i = 0; i < n - m - 1; i++)
    {
        b[j++] = a[i];
    }

    // printf("j=%d", j);
    printf("操作后数组为:");
    for (int i = 0; i < n; i++)
    {
        printf("%3d", b[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int n;
    int m;
    printf("请输入整数个数：\n");
    scanf("%d", &n);

    printf("请输入后移多少个位置:\n");
    scanf("%d", &m);

    srand(time(NULL));
    int a[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 20 + 1;
    }
    printf("原数组为:");
    for (int i = 0; i < n; i++)
    {
        printf("%3d", a[i]);
    }
    printf("\n");
    fun(a, n, m);

    return 0;
}