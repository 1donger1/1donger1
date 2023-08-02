#ifndef __DYNAMICARRAY_H_
#define __DYNAMICARRAY_H_
#include <stdio.h>
#include <stdlib.h>
#include "../Mysort/Mysort.h"
// #define Init_ArrayPoint(name, log)                           \
//     DMArrayList *name = (DMArrayList *)malloc(sizeof(DMArrayList)); \
//     if (name == NULL)                                        \
//     {                                                        \
//         printf("log");                                       \
//         return NULL;                                         \
//     }                                                        \
//     name->len = 0;

#define false 0
#define true 1

#define GROWTH_FACTOR 2
// #define Max 20
#define ElementType int
struct DynamicArray
{

    ElementType *dp; // 动态数组指针
    int size;        // 堆上申请的单位空间个数
    int len;         // 元素的个数
};
typedef struct DynamicArray DMArray; 

int ArrayInit(DMArray *array, int size);

void ReallocArray(DMArray *array);

void FreeArray(DMArray *array);

void Travel(DMArray *array);
/**********************插**入*****************************/

// 尾插法
void InsertTail(DMArray *array, ElementType element);

// 头插法
void InsertHead(DMArray *array, ElementType element);

// 中间插入--index为索引下标
void InsertIndex(DMArray *array, ElementType element, int index);

/**********************删**除*****************************/

// 按下标删除
void RemoveIndex(DMArray *array, int index);

// 按值删除
void RemoveElem(DMArray *array, ElementType elem);

int *FindElem(DMArray *array, int elem);

/********************修**改*******************************/

// 按位修改
void SetValueIndex(DMArray *array, int index, ElementType element);

// 按值修改
void SetValueElem(DMArray *array, ElementType oldValue, ElementType newValue);

/***********************找交并集、归并*****************************/

// 交集
DMArray *FindIntersection(DMArray *array1, DMArray *array2);

// 去重
void Deduplication(DMArray *array);

// 并集
DMArray *FindUnionSet(DMArray *array1, DMArray *array2);

// 归并
DMArray *MergeArray(DMArray *array1, DMArray *array2);



#endif