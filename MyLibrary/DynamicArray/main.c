// #include <stdio.h>
#include "DynamicArray.h"

int main(int argc, char *argv[])
{
    // 动态数组
#if 0
    // DMArray array = {NULL, 10, 0};
    DMArray array;
    ArrayInit(&array, 10);

    for (int i = 0; i < 15; i++)
    {
        InsertHead(&array, i + 1);
    }
    Travel(&array);
    FreeArray(&array);
#endif
#if 0 // 找交集之前的测试
    DMArray a;
    int size = 10; // 初始容量为10

    ArrayInit(&a, size);

    for (int i = 0; i < 10; i++)
    {
        InsertTail(&a, i + 1);
        // InsertHead(&a, i + 1);
    }
    printf("操作之前：");
    Travel(&a);

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
    // SetValueElem(&a, 1, 77);
    // Travel(&a);

    FreeArray(&a);
#endif
/****************************************************/
#if 1
    DMArray a1;
    int size = 10; // 初始容量为10

    ArrayInit(&a1, size);
    InsertTail(&a1, 1);
    InsertTail(&a1, 2);
    InsertTail(&a1, 3);
    InsertTail(&a1, 3);
    InsertTail(&a1, 3);
    InsertTail(&a1, 4);
    InsertTail(&a1, 5);
    InsertTail(&a1, 6);
    Travel(&a1);

    DMArray a2;
    ArrayInit(&a2, size);

    InsertTail(&a2, 5);
    InsertTail(&a2, 14);
    InsertTail(&a2, 3);
    InsertTail(&a2, 12);
    InsertTail(&a2, 1);
    InsertTail(&a2, 10);
    Travel(&a2);

    DMArray *intersection = FindIntersection(&a1, &a2);
    if (intersection != NULL)
    {
        // printf("intersection\n");
        Travel(intersection);
    }
    free(intersection->dp);

    // Deduplication(&a1);
    FindUnionSet(&a1, &a2);

    // DMArray *a3 = MergeArray(&a1, &a2);

    // DMArray *a3 = (DMArray *)malloc(sizeof(DMArray));
    // ArrayInit(a3, size);
    // a3 = MergeArray(&a1, &a2);

    // Travel(a3);

    FreeArray(&a1);
    FreeArray(&a2);
    // FreeArray(a3);

#endif

    return 0;
}
