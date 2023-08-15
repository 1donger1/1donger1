#ifndef __SORT_H_
#define __SORT_H_

#define N 10

void initnum(int *a, int n);

void print(int a[], int n);

void swap(int *x, int *y);

void Bubblesort(int *a, int n);
void Bubblesort2(int *a, int n);
void BubbleSort(int *a, int n);

void choosesort(int *a, int n);

void insertsort(int *a, int n);

void groupsort(int *a, int n, int pos, int step);
void shellsort(int *a, int n);

int part(int *a, int start, int end);
void QuickSort(int *a, int start, int end);

void quicksort(int *a, int start, int end);

#endif