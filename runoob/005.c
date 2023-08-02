#include <stdio.h>
#include <stdlib.h>

// 输入三个整数x,y,z，请把这三个数由小到大输出。

int main(int argc, char *argv[])
{
    int x, y, z;
    int arr[3] = {};
    printf("\n请输入三个数字:\n");
    scanf("%d %d %d", &x, &y, &z);
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;

    int i = 0, j = 0, temp;
    int len = sizeof(arr) / sizeof(arr[0]);
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("从小到大排序:\n");
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}