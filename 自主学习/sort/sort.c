#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initnum(int *a, int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
    printf("原序列为:");
    print(a, n);
}

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%3d", a[i]);
    }
    printf("\n");
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void Bubblesort(int *a, int n)
{
    int i, j;
    int flag;
    if (n < 2)
    {
        return;
    }
    for (i = n - 1; i > 1; i--)
    {
        flag = 0;
        for (j = 0; j < i; j++)
        {
            if (a[j] < a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("冒泡排序后:");
            print(a, n);
            return;
        }
    }
}
void BubbleSort(int *a, int n)
{
    int i, j;
    int flag;
    if (n < 2)
    {
        return;
    }
    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("冒泡排序后:");
            print(a, n);
            return;
        }
    }
}

void Bubblesort2(int *a, int n)
{
    if (n < 2)
    {
        return;
    }
    int i, flag = 0;
    for (i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
        {
            swap(&a[i], &a[i + 1]);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        printf("冒泡递归后:");
        print(a, n);
        return;
    }
    Bubblesort2(a, --n);
}

void choosesort(int *a, int n)
{
    if (n < 2)
    {
        return;
    }
    int i, j, temp, pos;
    for (i = 0; i < n - 1; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[pos])
            {
                pos = j;
            }
        }
        if (pos != i)
        {
            swap(&a[pos], &a[i]);
        }
    }
    printf("选择排序:");
    print(a, n);
}

void insertsort(int *a, int n)
{
    if (n < 2)
    {
        return;
    }
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        temp = a[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (a[j] <= temp)
            {
                break;
            }
            a[j + 1] = a[j]; // 元素后移
        }
        // printf("j = %d\n", j);
        a[j + 1] = temp;
    }
    printf("插入排序:");
    print(a, n);
}

void groupsort(int *a, int n, int pos, int step)
{
    int temp, i, j;
    for (i = pos + step; i < n; i += step)
    {
        temp = a[i];
        for (j = i - step; j >= 0; j -= step)
        {
            if (a[j] <= temp)
            {
                break;
            }
            a[j + step] = temp;
        }
    }
}
void shellsort(int *a, int n)
{
    if (n < 2)
    {
        return;
    }
    int i, step;
    for (step = n / 2; step > 0; step /= 2)
    {
        for (i = 0; i < step; i++)
        {
            groupsort(a, n, i, step);
        }
    }
    printf("希尔排序后:");
    print(a, n);
}

void quicksort(int *a, int start, int end)
{

    if (start >= end)
    {
        return;
    }
    int temp = a[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && a[right] >= temp)
        {
            right--;
        }
        if (left < right)
        {
            a[left] = a[right];
        }
        while (left < right && a[left] < temp)
        {
            left++;
        }
        if (left < right)
        {
            a[right] = a[left];
        }
    }
    a[left] = temp;
    quicksort(a, start, left - 1);
    quicksort(a, left + 1, end);
}
int part(int *a, int start, int end)
{
    int pivot = a[start];
    while (start < end)
    {
        while (start < end && a[end] >= pivot)
        {
            end--;
        }
        a[start] = a[end];
        while (start < end && a[start] <= pivot)
        {
            start++;
        }
        a[end] = a[start];
    }
    a[start] = pivot;
    return start;
}

void QuickSort(int *a, int start, int end)
{
    if (start < end)
    {
        int pivotpos = part(a, start, end);
        QuickSort(a, start, pivotpos - 1);
        QuickSort(a, pivotpos + 1, end);
    }
}