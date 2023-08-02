#ifndef __ARRAYLIB_H_
#define __ARRAYLIB_H_
#include <stdio.h>
#include <stdlib.h>
#include "../../../MyLibrary/Mysort/Mysort.h"
#define GROWTH_FACTOR 2
#define ElementType int

// #define Init_ArrayPoint(name, log)                           \
//     DMArrayList *name = (DMArrayList *)malloc(sizeof(DMArrayList)); \
//     if (name == NULL)                                        \
//     {                                                        \
//         printf("log");                                       \
//         return NULL;                                         \
//     }                                                        \
//     name->len = 0;

struct Array
{
    ElementType *array;
    int len;
    int capacity;
};
typedef struct Array DMArrayList;

void InitDynamicArrayList(DMArrayList *da, int initialCapacity);

void ReallocDynamicArrayList(DMArrayList *da);

void FreeDynamicArrayList(DMArrayList *da);

void Travel(DMArrayList *da);

// 尾插法
void InsertTail(DMArrayList *da, ElementType element);

// 头插法
void InsertHead(DMArrayList *da, ElementType element);

// 中间插入--index为索引下标
void InsertIndex(DMArrayList *da, ElementType element, int index);

// 按下标删除
void RemoveIndex(DMArrayList *a, int index);

// 按值删除
void RemoveElem(DMArrayList *a, ElementType elem);

// 按索引查找
ElementType *FindIndex(DMArrayList *a, int index);

// 按值查找
// 法二：
int *FindElem(DMArrayList *a, int elem);

// 按位修改
void SetValueIndex(DMArrayList *a, int index, ElementType element);
// 按值修改
void SetValueElem(DMArrayList *a, ElementType oldValue, ElementType newValue);

void Deduplication(DMArrayList *array);

// 交集
DMArrayList *FindIntersection(DMArrayList *array1, DMArrayList *array2);

// 并集
DMArrayList *FindUnionSet(DMArrayList *array1, DMArrayList *array2);

// 归并
DMArrayList *MergeArray(DMArrayList *array1, DMArrayList *array2);

#endif