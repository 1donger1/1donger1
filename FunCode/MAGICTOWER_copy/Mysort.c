#include "Mysort.h"
// #include <stdio.h>

int IsSmaller(int a, int b)
{
    if (a < b)
        return 1;
    else
        return 0;
}

int IsBiggr(int a, int b)
{
    if (a < b)
        return 0;
    else
        return 1;
}

void BubbleSort(int *a, int len, int (*Rule)(int, int))
{
    for (int i = 0; i < len - 1; i++)
    {
        int flag = 0;
        for (int j = 0; j < len - i - 1; j++)
        {
            if (Rule(a[j], a[j + 1]))
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
}

void InserSort(int *a, int len)
{
    for (int i = 1; i < len; i++)
    {
        int temp = a[i];
        int j = 0;
        for (j = i; j > 0; j--)
        {
            if (a[j - 1] > temp)
            {
                a[j] = a[j - 1];
            }
            else
            {
                break;
            }
        }
        a[j] = temp;
    }
}

void ChooseSort(int *a, int len)
{
    for (int i = 0; i < len; i++)
    {
        int min = i;
        int Minum = a[min];
        for (int j = i + 1; j < len; j++)
        {
            if (a[j] < Minum)
            {
                Minum = a[j];
                min = j;
            }
        }
        int temp = a[i];
        a[i] = Minum;
        a[min] = temp;
    }
}

void ChooseSort2(int *a, int len)
{
    int left = 0;
    int right = len - 1;
    while (left < right)
    {
        int min = left;
        int max = right;
        for (int i = left; i <= right; i++)
        {
            if (a[i] < a[min])
                min = i;
            if (a[i] > a[max])
                max = i;
        }

        int temp = a[left];
        a[left] = a[min];
        a[min] = temp;

        if (min != right || min != right)
        {
            temp = a[right];
            a[right] = a[max];
            a[max] = temp;
        }

        left++;
        right--;
    }
}

// void Quicksort(int *a, int start, int end)
// {
//     int temp = a[start];
//     int left = start;
//     int right = end;
//     while (left < right)
//     {
//         while (left < right && temp < a[right])
//         {
//             right--;
//         }
//         if (left < right)
//         {
//             a[left] = a[right];
//             left++;
//         }
//         while (left < right && temp > a[left])
//         {
//             left++;
//         }
//         if (left < right)
//         {
//             a[left] = a[right];
//             right--;
//         }
//         while (temp > a[left])
//         {
//             left++;
//         }
//         a[left] = temp;

//         Quicksort(a, start, left - 1);
//         Quicksort(a, right + 1, end);
//     }
// }
void Quicksort(int *a, int start, int end)
{
    if (start >= end)
        return;
    int temp = a[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && a[right] >= temp)
            right--;
        if (left < right)
            a[left] = a[right];
        while (left < right && a[left] < temp)
            left++;
        if (left < right)
            a[right] = a[left];
    }
    a[left] = temp;
    Quicksort(a, start, left - 1);
    Quicksort(a, left + 1, end);
}