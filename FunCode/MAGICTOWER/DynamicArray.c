#include <stdlib.h>
#include <stdio.h>
#include "DynamicArray.h"

int ArrayInit(DMArray *array)
{
    // 申请堆上空间 size*数据类型的大小
    array->dp = (ElementType *)malloc(sizeof(ElementType)); //(强制类型转换)malloc(sizeof(int)*个数)
    // 判断是否申请成功
    if (array->dp == NULL)
    {
        // 申请失败，打印错误信息，返回false
        printf("ArrayInit error!\n");
        return false;
    }

    return true;
}

// 释放申请的空间
void FreeArray(DMArray *array)
{
    // 判断指针不为空，我释放空指针会出错
    if (array->dp != NULL)
    {
        free(array->dp);
        // 放空后指针要置空
        array->dp = NULL;
    }
}
// 扩容动态数组
void ReallocArray(DMArray *array)
{
    ElementType *temp = array->dp;
    int newsize = array->size * GROWTH_FACTOR;
    ElementType *newArray = (ElementType *)malloc(newsize * sizeof(ElementType));
    if (newArray == NULL)
    {
        printf("ReallocDynamicArrayList malloc error!\n");
        return;
    }

    // Copy elements
    for (int i = 0; i < array->len; i++)
    {
        newArray[i] = temp[i];
    }

    array->dp = newArray;
    array->size = newsize;
    // 释放原先的内存空间
    free(temp);
    // return true;
}
// void Travel(DMArray *array)
// {
//     for (int i = 0; i < array->len; i++)
//     {
//         printf("%d ", array->dp[i]);
//     }
//     printf("\n");
// }

/**********************插**入*****************************/
// 尾插法
// void InsertTail(DMArray *array, ElementType element)
// {
//     if (array->len >= array->size)
//     {
//         // 动态数组满了，需要扩容
//         // array->size *= 2;
//         // array->array = (ElementType *)realloc(array->array, array->size * sizeof(ElementType));
//         ReallocArray(array);
//     }

//     array->dp[array->len] = element;
//     array->len++;
// }

void InsertArray(DMArray *array, ElementType element)
{
    if (array->len >= array->size)
    {
        // 动态数组满了，需要扩容
        // array->size *= 2;
        // array->array = (ElementType *)realloc(array->array, array->size * sizeof(ElementType));
        ReallocArray(array);
    }

    array->dp[array->len] = element;
    array->len++;
}

// // 头插法
// void InsertHead(DMArray *array, ElementType element)
// {
//     if (array->len >= array->size)
//     {
//         // 动态数组满了，需要扩容
//         // array->size *= 2;
//         // array->array = (ElementType *)realloc(array->array, array->size * sizeof(ElementType));
//         ReallocArray(array);
//     }

//     for (int i = array->len; i > 0; i--)
//     {
//         array->dp[i] = array->dp[i - 1];
//     }
//     array->dp[0] = element;
//     array->len++;
// }

// // 中间插入--index为索引下标
// void InsertIndex(DMArray *array, ElementType element, int index)
// {
//     if (index < 0 || index > array->len)
//     {
//         printf("InsertIndex invalid place!\n");
//     }

//     if (array->len >= array->size)
//     {
//         // 动态数组满了，需要扩容
//         // array->size *= 2;
//         // array->array = (ElementType *)realloc(array->array, array->size * sizeof(ElementType));
//         ReallocArray(array);
//     }

//     for (int i = array->len; i >= index; i--)
//     {
//         array->dp[i + 1] = array->dp[i];
//     }
//     array->dp[index] = element;
//     array->len++;
// }

/**********************删**除*****************************/
#if 1
// 按下标删除
void RemoveIndex(DMArray *array, int index)
{
    if (index < 0 || index >= array->len)
    {
        printf("RemoveIndex invalid place!\n");
        return;
    }

    for (int i = index; i < array->len - 1; i++)
    {
        array->dp[i] = array->dp[i + 1];
    }
    array->len--;
}

// 按值删除
void RemoveElem(DMArray *array, ElementType elem)
{
    for (int i = 0; i < array->len; i++)
    {
        if (array->dp[i] == elem)
        {
            RemoveIndex(array, i);
            i--;
        }
    }
}
#endif

/*********************查**找******************************/
#if 0
// 按索引查找
ElementType *FindIndex(DMArray *array, int index)
{
    if (index < 0 || index >= array->len)
    {
        printf("FindIndex invalid place!\n");
        return NULL;
    }
    return &array->dp[index];
}

// 按值查找
// 法一：
// int *FindElem(DMArray *array, int elem)
// {

//     // 问题：这行代码的意义，为什么malloc,为什么(array->len)+1
//     int *FindVector = (int *)malloc(sizeof(int) * (array->len + 1));
//     int count = 0;

//     if (FindVector == NULL)
//     {
//         printf("malloc error!\n");
//         return NULL;
//     }
//     for (int i = 0; i < array->len; i++)
//     {
//         if (array->dp[i] == elem)
//         {
//             count++; // 先++再放值
//             FindVector[count] = i;
//         }
//     }

//     FindVector[0] = count;
//     return FindVector;
// }

// 法二
int *FindElem(DMArray *array, int elem)
{
    // 问题：这行代码的意义，为什么malloc,为什么(a->len)+1
    int *FindVector = (int *)malloc(sizeof(int) * (array->len + 1));
    int count = 0;

    if (FindVector == NULL)
    {
        printf("malloc error!\n");
        return NULL;
    }
    for (int i = 0; i < array->len; i++)
    {
        if (array->dp[i] == elem)
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
#if 0
// 按位修改
void SetValueIndex(DMArray *array, int index, ElementType element)
{
    if (index < 0 || index >= array->len)
    {
        printf("FindIndex invalid place!\n");
        return;
    }

    array->dp[index] = element;
}

// 按值修改
void SetValueElem(DMArray *array, ElementType oldValue, ElementType newValue)
{
    for (int i = 0; i < array->len; i++)
    {
        if (array->dp[i] == oldValue)
        {
            array->dp[i] = newValue;
        }
    }
}
#endif

/***********************找交并集、归并*****************************/
#if 0
// 交集
DMArray *FindIntersection(DMArray *array1, DMArray *array2)
{
    // malloc
    DMArray *intersection = (DMArray *)malloc(sizeof(DMArray));
    // if
    if (intersection == NULL)
    {
        printf("FindIntersection malloc error!");
        return NULL;
    }
    ArrayInit(intersection, array1->len + array2->len);

    // init
    intersection->len = 0;
    for (int i = 0; i < array1->len; i++)
    {
        for (int j = 0; j < array2->len; j++)
        {
            if (array1->dp[i] == array2->dp[j])
            {
                int flag = 0;
                for (int k = 0; k < intersection->len; k++)
                {
                    if (intersection->dp[k] == array1->dp[i])
                    {
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    InsertTail(intersection, array1->dp[i]);
                }
            }
        }
    }
    Travel(intersection);
    return intersection;
}

// 去重
void Deduplication(DMArray *array)
{
    // printf("In Depulication!\n");
    Travel(array);
    Quicksort(array->dp, 0, array->len - 1);
    for (int i = 1; i < array->len; i++)
    {
        if (array->dp[i] == array->dp[i - 1])
        {
            RemoveIndex(array, i);
            i--;
        }
    }
    // Travel(array);
}
// 并集
DMArray *FindUnionSet(DMArray *array1, DMArray *array2)
{
    DMArray *UnionSet = (DMArray *)malloc(sizeof(DMArray));
    // if (UnionSet == NULL)
    // {
    //     printf("FindUnionSet malloc error!\n");
    //     return NULL;
    // }
    // UnionSet->len = 0;

    // DMArray *UnionSet;
    // printf("array1->len=%d array2->len%d\n", array1->len, array2->len);
    ArrayInit(UnionSet, array1->len + array2->len);
    // printf("after ArraInit Unionset\n");
    // printf("%d %d \n", UnionSet->size, UnionSet->len);
    // Travel(UnionSet);

    for (int i = 0; i < array1->len; i++)
    {
        InsertTail(UnionSet, array1->dp[i]);
    }

    for (int i = 0; i < array2->len; i++)
    {
        InsertTail(UnionSet, array2->dp[i]);
    }

    Deduplication(UnionSet);
    return UnionSet;
}
// 归并
DMArray *MergeArray(DMArray *array1, DMArray *array2)
{
    Quicksort(array1->dp, 0, array1->len - 1);
    printf("sort array1\n");
    Travel(array1);
    
    Quicksort(array2->dp, 0, array2->len - 1);
    printf("sort array2\n");
    Travel(array2);

    // DMArray *merge;
    DMArray *merge = (DMArray *)malloc(sizeof(DMArray));
    // printf("before!");
    if (merge == NULL)
    {
        printf("MergeArray malloc error!\n");
        return NULL;
    }

    // printf("before! ArrayInit\n");
    ArrayInit(merge, array1->len + array2->len);
    // printf("after ArrayInit!\n");
    // printf("%d %d \n", merge->size, merge->len);
    Travel(merge);

    /*********************************/
    // DMArray *merge = (DMArray *)malloc(sizeof(DMArray));
    // if(merge == NULL)
    // {
    //     printf("Malloc merge Error\n");
    //     return NULL;
    // }
    // merge->size = 50;
    // merge->len = 0;
    // merge->dp = (ElementType *)malloc(sizeof(ElementType) * merge->size);
    /*********************************/

    int i = 0, j = 0;
    while (i < array1->len && j < array2->len)
    {
        if (array1->dp[i] < array2->dp[j])
        {
            InsertTail(merge, array1->dp[i]);
            // printf("%d %d \n", merge->size, merge->len);
            i++;
        }
        else
        {
            InsertTail(merge, array2->dp[j]);
            j++;
        }
    }
    while (i < array1->len)
    {
        InsertTail(merge, array1->dp[i]);
        i++;
        // printf("hhhhhh%d %d \n", merge->size, merge->len);
    }
    while (j < array2->len)
    {
        InsertTail(merge, array2->dp[j]);
        j++;
        // printf("xxxxxxxxxxx%d %d \n", merge->size, merge->len);
    }

    printf("归并!\n");
    Travel(merge);

    return merge;
}
#endif
