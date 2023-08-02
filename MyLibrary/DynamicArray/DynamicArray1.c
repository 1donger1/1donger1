// #include <stdio.h>
// #include <stdlib.h>
#include "DynamicArray1.h"

int ArrayInit(DMarray *array)
{
    array->dp = (ElementType *)malloc(array->size * sizeof(ElementType));
    if (array->dp == NULL)
    {
        printf("Malloc Error\n");
        return false;
    }

    return 0;
}

void FreeArray(DMarray *array)
{
    if (array->dp != NULL)
    {
        free(array->dp);
        array->dp = NULL;
    }
}

int ReallocArray(DMarray *array)
{
    ElementType *temp = array->dp;
    array->dp = (ElementType *)malloc(sizeof(ElementType) * array->size * 2);
    if (array->dp == NULL)
    {
        printf("ReallocArray Error\n");
        return false;
    }

    // 拷贝
    for (int i = 0; i < array->len; i++)
    {
        array->dp[i] = temp[i];
    }

    array->size *= 2;
    free(temp);
    return true;
}

int InsertArray(DMarray *array, ElementType element)
{
    if (array->len == array->size)
    {
        if (ReallocArray(array) == false)
        {
            printf("can not contain more element\n");
            return false;
        }
    }

    array->dp[array->len++] = element;

    return true;
}
void travel(DMarray *array)
{
    printf("array len:%d array size: %d\n", array->len, array->size);

    for (int i = 0; i < array->len; i++)
    {
        printf("%d ", array->dp[i]);
    }
    printf("\n");
}

/*********************************************************************************************/
// 初始化动态数组
void InitDynamicArrayList(DMArrayList *da, int initialCapacity)
{
    da->array = (ElementType *)malloc(initialCapacity * sizeof(ElementType));
    da->len = 0;
    da->capacity = initialCapacity;
    if (da->array == NULL)
    {
        printf("InitDynamicArrayList malloc error!\n");
        return;
    }
}

void ReallocDynamicArrayList(DMArrayList *da)
{
    printf("Use ReallocDynamicArrayList!\n");
    ElementType *temp = da->array;
    int newCapacity = da->capacity * GROWTH_FACTOR;
    ElementType *newArray = (ElementType *)malloc(newCapacity * sizeof(ElementType));
    if (newArray == NULL)
    {
        printf("ReallocDynamicArrayList malloc error!\n");
        return;
    }

    // Copy elements
    for (int i = 0; i < da->len; i++)
    {
        newArray[i] = temp[i];
    }

    da->array = newArray;
    da->capacity = newCapacity;
    free(temp);
}

// 释放动态数组的内存
void FreeDynamicArrayList(DMArrayList *da)
{
    free(da->array);
}

// 遍历动态数组
void Travel(DMArrayList *da)
{
    for (int i = 0; i < da->len; i++)
    {
        printf("%d ", da->array[i]);
    }
    printf("\n");
}

/**********************插**入*****************************/
// 尾插法
void InsertTail(DMArrayList *da, ElementType element)
{
    if (da->len >= da->capacity)
    {
        // 动态数组满了，需要扩容
        // da->capacity *= 2;
        // da->array = (ElementType *)realloc(da->array, da->capacity * sizeof(ElementType));
        ReallocDynamicArrayList(da);
    }

    da->array[da->len] = element;
    da->len++;
}

// 头插法
void InsertHead(DMArrayList *da, ElementType element)
{
    if (da->len >= da->capacity)
    {
        // 动态数组满了，需要扩容
        // da->capacity *= 2;
        // da->array = (ElementType *)realloc(da->array, da->capacity * sizeof(ElementType));
        ReallocDynamicArrayList(da);
    }

    for (int i = da->len; i > 0; i--)
    {
        da->array[i] = da->array[i - 1];
    }
    da->array[0] = element;
    da->len++;
}

// 中间插入--index为索引下标
void InsertIndex(DMArrayList *da, ElementType element, int index)
{
    if (index < 0 || index > da->len)
    {
        printf("InsertIndex invalid place!\n");
    }

    if (da->len >= da->capacity)
    {
        // 动态数组满了，需要扩容
        // da->capacity *= 2;
        // da->array = (ElementType *)realloc(da->array, da->capacity * sizeof(ElementType));
        ReallocDynamicArrayList(da);
    }

    for (int i = da->len; i >= index; i--)
    {
        da->array[i + 1] = da->array[i];
    }
    da->array[index] = element;
    da->len++;
}

/**********************删**除*****************************/
#if 1
// 按下标删除
void RemoveIndex(DMArrayList *a, int index)
{
    if (index < 0 || index >= a->len)
    {
        printf("RemoveIndex invalid place!\n");
        return;
    }

    for (int i = index; i < a->len - 1; i++)
    {
        a->array[i] = a->array[i + 1];
    }
    a->len--;
}

// 按值删除
void RemoveElem(DMArrayList *a, ElementType elem)
{
    for (int i = 0; i < a->len; i++)
    {
        if (a->array[i] == elem)
        {
            RemoveIndex(a, i);
            i--;
        }
    }
}
#endif

/*********************查**找******************************/
#if 1
// 按索引查找
ElementType *FindIndex(DMArrayList *a, int index)
{
    if (index < 0 || index >= a->len)
    {
        printf("FindIndex invalid place!\n");
        return NULL;
    }
    return &a->array[index];
}

// 按值查找
// 法一：
// int *FindElem(DMArrayList *a, int elem)
// {

//     // 问题：这行代码的意义，为什么malloc,为什么(a->len)+1
//     int *FindVector = (int *)malloc(sizeof(int) * (a->len + 1));
//     int count = 0;

//     if (FindVector == NULL)
//     {
//         printf("malloc error!\n");
//         return NULL;
//     }
//     for (int i = 0; i < a->len; i++)
//     {
//         if (a->array[i] == elem)
//         {
//             count++; // 先++再放值
//             FindVector[count] = i;
//         }
//     }

//     FindVector[0] = count;
//     return FindVector;
// }

// 法二
int *FindElem(DMArrayList *a, int elem)
{
    // 问题：这行代码的意义，为什么malloc,为什么(a->len)+1
    int *FindVector = (int *)malloc(sizeof(int) * (a->len + 1));
    int count = 0;

    if (FindVector == NULL)
    {
        printf("malloc error!\n");
        return NULL;
    }
    for (int i = 0; i < a->len; i++)
    {
        if (a->array[i] == elem)
        {
            FindVector[count] = i;
            count++;
        }
    }
    FindVector[count] = -1;
    return FindVector;
}
#endif

/********************修**改*******************************/
#if 1
// 按位修改
void SetValueIndex(DMArrayList *a, int index, ElementType element)
{
    if (index < 0 || index >= a->len)
    {
        printf("FindIndex invalid place!\n");
        return;
    }

    a->array[index] = element;
}

// 按值修改
void SetValueElem(DMArrayList *a, ElementType oldValue, ElementType newValue)
{
    for (int i = 0; i < a->len; i++)
    {
        if (a->array[i] == oldValue)
        {
            a->array[i] = newValue;
        }
    }
}
#endif

/***********************找交并集、归并*****************************/
#if 1
// 交集
DMArrayList *FindIntersection(DMArrayList *array1, DMArrayList *array2)
{
    // malloc
    DMArrayList *intersection = (DMArrayList *)malloc(sizeof(DMArrayList));
    // if
    if (intersection == NULL)
    {
        printf("FindIntersection malloc error!");
        return NULL;
    }
    // init
    intersection->len = 0;
    for (int i = 0; i < array1->len; i++)
    {
        for (int j = 0; j < array2->len; j++)
        {
            if (array1->array[i] == array2->array[j])
            {
                int flag = 0;
                for (int k = 0; k < intersection->len; k++)
                {
                    if (intersection->array[k] == array1->array[i])
                    {
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    InsertTail(intersection, array1->array[i]);
                }
            }
        }
    }
    return intersection;
}

// 去重
void Deduplication(DMArrayList *array)
{
    Quicksort(array->array, 0, array->len - 1);
    for (int i = 1; i < array->len; i++)
    {
        if (array->array[i] == array->array[i - 1])
        {
            RemoveIndex(array, i);
            i--;
        }
    }
    Travel(array);
}
// 并集
DMArrayList *FindUnionSet(DMArrayList *array1, DMArrayList *array2)
{
    DMArrayList *UnionSet = (DMArrayList *)malloc(sizeof(DMArrayList));
    // if (UnionSet == NULL)
    // {
    //     printf("FindUnionSet malloc error!\n");
    //     return NULL;
    // }
    // UnionSet->len = 0;
    // DMArrayList *UnionSet;

    InitDynamicArrayList(UnionSet, array1->len+array2->len-1);

    for (int i = 0; i < array1->len; i++)
    {
        InsertTail(UnionSet, array1->array[i]);
    }

    for (int i = 0; i < array2->len; i++)
    {
        InsertTail(UnionSet, array2->array[i]);
    }

    Deduplication(UnionSet);
    return UnionSet;
}
// 归并
DMArrayList *MergeArray(DMArrayList *array1, DMArrayList *array2)
{
    Quicksort(array1->array, 0, array1->len - 1);
    Quicksort(array2->array, 0, array2->len - 1);

    DMArrayList *merge;
    merge = (DMArrayList *)malloc(sizeof(DMArrayList));
    if (merge == NULL)
    {
        printf("MergeArray malloc error!\n");
        return NULL;
    }
    InitDynamicArrayList(merge, array1->len + array2->len);
    int i = 0, j = 0;
    while (i < array1->len && j < array2->len)
    {
        if (array1->array[i] < array2->array[j])
        {
            InsertTail(merge, array1->array[i]);
            i++;
        }
        else
        {
            InsertTail(merge, array2->array[j]);
            j++;
        }
    }
    while (i < array1->len)
    {
        InsertTail(merge, array1->array[i]);
        i++;
    }
    while (j < array2->len)
    {
        InsertTail(merge, array2->array[j]);
        j++;
    }
    return merge;
}
#endif