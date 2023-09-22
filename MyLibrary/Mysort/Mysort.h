#ifndef __MYSORT_H_
#define ___MYSORT_H_
#include <stdio.h>

#define ArrayLen(a) sizeof(a) / sizeof(a[0])

int IsSmaller(int a, int b);
int IsBiggr(int a, int b);
void BubbleSort(int *a, int len, int (*Rule)(int, int));
void InsertSort(int *a, int len);
void ChooseSort(int *a, int len);
void ChooseSort2(int *a, int len);
void Quicksort(int *a, int start, int end);


#endif