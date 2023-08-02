#include <stdio.h>
#include <stdlib.h>
#include "../../../MyLibrary/Mysort/Mysort.h"
#define Max 20
#define ElementType int

#define Init_ArrayPoint(name, log)                                     \
    struct Array *name = (struct Array *)malloc(sizeof(struct Array)); \
    if (name == NULL)                                                  \
    {                                                                  \
        printf("log");                                                 \
        return NULL;                                                   \
    }                                                                  \
    name->len = 0;
#define FreeArrayPoint(name) \
    if (name != NULL)        \
    {                        \
        free(name);          \
        name = NULL;         \
    }

struct Array
{
    ElementType array[Max];
    int len;
};

// 遍历
void Travel(struct Array *a)
{
    for (int i = 0; i < a->len; i++)
    {
        printf("%d ", a->array[i]);
    }
    printf("\n");
}

/***********************插**入****************************/
#if 1
// 尾插法
void InsertTail(struct Array *a, ElementType element)
{
    if (a->len >= Max)
    {
        printf("InsertTail out of range\n");
        return;
    }

    a->array[a->len] = element;
    a->len++;
}

// 头插法
void InsertHead(struct Array *a, ElementType element)
{
    if (a->len >= Max)
    {
        printf("InsertHead out of range\n");
        return;
    }

    // for (int i = a->len - 1; i >= 0;i--)
    // {
    //     a->array[i + 1] = a->array[i];
    // }
    for (int i = a->len; i > 0; i--)
    {
        a->array[i] = a->array[i - 1];
    }
    a->array[0] = element;
    a->len++;
}

// 中间插入--index为索引下标
void InsertIndex(struct Array *a, ElementType element, int index)
{
    if (index < 0 || index > a->len)
    {
        printf("InsertIndex invalid place!\n");
    }

    if (a->len >= Max)
    {
        printf("InsertIndex out of range\n");
        return;
    }
    for (int i = a->len; i >= index; i--)
    {
        a->array[i + 1] = a->array[i];
    }
    // for (int i = a->len; i > index; i--)
    // {
    //     a->array[i] = a->array[i - 1];
    // }
    a->array[index] = element;
    a->len++;
}
#endif

/**********************删**除*****************************/
#if 1
// 按下标删除
void RemoveIndex(struct Array *a, int index)
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
void RemoveElem(struct Array *a, ElementType elem)
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
ElementType *FindIndex(struct Array *a, int index)
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
// int *FindElem(struct Array *a, int elem)
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
int *FindElem(struct Array *a, int elem)
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
void SetValueIndex(struct Array *a, int index, ElementType element)
{
    if (index < 0 || index >= a->len)
    {
        printf("FindIndex invalid place!\n");
        return;
    }

    a->array[index] = element;
}

// 按值修改
void SetValueElem(struct Array *a, ElementType oldValue, ElementType newValue)
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
struct Array *FindIntersection(struct Array *array1, struct Array *array2)
{
    // malloc
    struct Array *intersection = (struct Array *)malloc(sizeof(struct Array));
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
void Deduplication(struct Array *array)
{
    printf("Before Deduplication:");
    Travel(array);

    Quicksort(array->array, 0, array->len - 1);
    printf("After:");
    Travel(array);

    for (int i = 1; i < array->len; i++)
    {
        if (array->array[i] == array->array[i - 1])
        {
            RemoveIndex(array, i);
            i--;
        }
    }
}
// 并集
struct Array *FindUnionSet(struct Array *array1, struct Array *array2)
{
    struct Array *UnionSet = (struct Array *)malloc(sizeof(struct Array));
    if (UnionSet == NULL)
    {
        printf("FindUnionSet malloc error!\n");
        return NULL;
    }
    UnionSet->len = 0;

    for (int i = 0; i < array1->len; i++)
    {
        InsertTail(UnionSet, array1->array[i]);
    }

    printf("FindUnionSet:");
    Travel(UnionSet);

    for (int i = 0; i < array2->len; i++)
    {
        InsertTail(UnionSet, array2->array[i]);
    }
    printf("FindUnionSet:");
    Travel(UnionSet);

    Deduplication(UnionSet);
    return UnionSet;
}
// 归并
struct Array *MergeArray(struct Array *array1, struct Array *array2)
{
    Quicksort(array1->array, 0, array1->len - 1);
    Quicksort(array2->array, 0, array2->len - 1);
    Init_ArrayPoint(merge, "MergeArray malloc error!");
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
        i++;
    }
    return merge;
}
#endif

/************************主函数*****************************/
int main(int argc, char *argv[])
{
#if 0 // 找交集之前的测试
    struct Array a;
    a.len = 0;

    for (int i = 0; i < 10; i++)
    {
        InsertTail(&a, i + 1);
        // InsertHead(&a, i + 1);
    }

    InsertIndex(&a, 66, 4);
    InsertIndex(&a, 66, 4);

    // RemoveIndex(&a, 6);
    // RemoveElem(&a, 66);

    Travel(&a);


    int *findVector = FindElem(&a, 66);
    /*//法一方式
    if (findVector != NULL)
    {
        int len = findVector[0];
        printf("find index :");
        for (int i = 1; i <= len; i++)
        {
            printf("[%d]\t", findVector[i]);
        }
        printf("\n");
        free(findVector);
    }*/

    // 法二方式
    if (findVector != NULL)
    {
        int *temp = findVector;
        while (*temp != -1)
        {
            printf("find index: %d\n", *temp);
            temp++;
        }

        free(findVector);
    }

    // SetValueIndex(&a, 1, 520);
    SetValueElem(&a, 1, 77);
    Travel(&a);
#endif
/****************************************************/
#if 1
    struct Array a1;
    a1.len = 0;
    InsertTail(&a1, 1);
    InsertTail(&a1, 4);
    InsertTail(&a1, 6);
    InsertTail(&a1, 8);
    Travel(&a1);

    struct Array a2;
    a2.len = 0;
    InsertTail(&a2, 2);
    InsertTail(&a2, 3);
    InsertTail(&a2, 4);
    InsertTail(&a2, 6);
    InsertTail(&a2, 5);
    InsertTail(&a2, 7);

    Travel(&a2);

    // struct Array *intersection = FindIntersection(&a1, &a2);
    // if (intersection != NULL)
    // {
    //     Travel(intersection);
    // }
    // free(intersection->array);

    // Deduplication(&a1);
    // FindUnionSet(&a1, &a2);
    struct Array *a3 = FindUnionSet(&a1, &a2);
    Travel(a3);

    // struct Array *a3 = MergeArray(&a1, &a2);
    // Travel(a3);

#endif

    return 0;
}
