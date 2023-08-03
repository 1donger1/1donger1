#include "LinkList.h"

int main(int argc, char *argv[])
{
    LinkList list;
    InitLinkList(&list);

    for (int i = 0; i < 10; i++)
    {
        InsertTail(&list, i + 1);
        // InsertHead(&list, i+1);
    }

    InsertIndex(&list, 7, 0);

    // RemoveByIndex(&list, 2);
    // RemoveByElement(&list, 10);

    Travel(&list);

    // printf("按索引查找:%d \n", *FindByIndex(&list, 1));

    // int *findvector = FindByElement(&list, 7);
    // if(findvector != NULL)
    // {
    //     int *temp = findvector;
    //     while(*temp != -1)
    //     {
    //         printf("find index: %d\n", *temp);
    //         temp++;
    //     }
    //     free(findvector);
    // }

    // SetValueByIndex(&list, 144, 1);
    // SetValueByIndex(&list, 144, 2);
    // SetValueByIndex(&list, 144, 3);
    // SetValueByIndex(&list, 144, 4);
    // printf("after SetValueByIndex\n");
    // Travel(&list);

    // SetValueByELement(&list, 144, 666);
    // printf("after SetValueByELement\n");
    // Travel(&list);

    // BubbleSort(&list);
    // printf("after BubbleSort\n");
    // Travel(&list);
    // Reverse(&list);
    // printf("after Reverse!\n");
    // Travel(&list);

    // list.head->next = Reverse2(list.head->next);
    // printf("after Reverse2!\n");
    // Travel(&list);

    // LinkList list1;
    // InitLinkList(&list1);
    // for (int i = 0; i < 10; i++)
    // {
    //     InsertTail(&list1, i + 2);
    //     // InsertHead(&list, i+1);
    // }
    // Travel(&list1);

    // LinkList list2;
    // InitLinkList(&list2);
    // for (int i = 0; i < 10; i++)
    // {
    //     InsertTail(&list2, i + 4);
    //     // InsertHead(&list, i+1);
    // }
    // Travel(&list2);

    // LinkList *mergedList = MergeList(&list1, &list2);
    // printf("after MergeList\n");
    // Travel(mergedList);

    return 0;
}