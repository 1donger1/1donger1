// #include <stdio.h>
#include "DynamicArray1.h"

int main(int argc, char *argv[])
{
    // 动态数组
#if 0
    DMarray array = {NULL, 10, 0};
    ArrayInit(&array);

    for (int i = 0; i < 15; i++)
    {
        InsertArray(&array, i + 1);
    }
    travelList(&array);
    FreeArray(&array);
#endif
#if 0 // 找交集之前的测试
    DMArrayList a;
    int initialCapacity = 10; // 初始容量为10

    InitDynamicArrayList(&a, initialCapacity);

    for (int i = 0; i < 10; i++)
    {
        InsertTail(&a, i + 1);
        // InsertHead(&a, i + 1);
    }
    printf("操作前的数据:");
    Travel(&a);

    InsertIndex(&a, 66, 4);
    InsertIndex(&a, 66, 4);

    // RemoveIndex(&a, 8);
    RemoveElem(&a, 10);

    Travel(&a);

    // int *findVector = FindElem(&a, 66);
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
    // if (findVector != NULL)
    // {
    //     int *temp = findVector;
    //     while (*temp != -1)
    //     {
    //         printf("find index: %d\n", *temp);
    //         temp++;
    //     }

    //     free(findVector);
    // }

    // SetValueIndex(&a, 1, 520);
    // SetValueElem(&a, 1, 77);
    Travel(&a);

    FreeDynamicArrayList(&a);
#endif
/****************************************************/
#if 1
    DMArrayList a1;
    int initialCapacity = 10; // 初始容量为10

    InitDynamicArrayList(&a1, initialCapacity);
    InsertTail(&a1, 1);
    InsertTail(&a1, 4);
    InsertTail(&a1, 6);
    InsertTail(&a1, 6);
    InsertTail(&a1, 6);
    InsertTail(&a1, 8);
    Travel(&a1);

    DMArrayList a2;
    InitDynamicArrayList(&a2, initialCapacity);

    InsertTail(&a2, 2);
    InsertTail(&a2, 3);
    InsertTail(&a2, 4);
    InsertTail(&a2, 6);
    InsertTail(&a2, 5);
    InsertTail(&a2, 7);
    Travel(&a2);

    // struct Array *intersection = FindIntersection(&a1, &a2);//交集
    // if (intersection != NULL)
    // {
    //     Travel(intersection);
    // }
    // free(intersection->array);

    // Deduplication(&a1);//去重
    // FindUnionSet(&a1, &a2);//并集

    DMArrayList *a3 = MergeArray(&a1, &a2);//归并
    Travel(a3);

    FreeDynamicArrayList(&a1);
    FreeDynamicArrayList(&a2);
    FreeDynamicArrayList(a3);

#endif

    return 0;
}
