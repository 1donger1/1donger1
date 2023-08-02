#include "DoubleCircleLinkList.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    DCLlist list;
    InitDCLlist(&list);

    for (int i = 0; i < 13; i++)
    {
        InsertTail(&list, i+1);
        // InsertHead(&list, i+1);
    }

    // InsertHead(&list, 0);
    // InsertHead(&list, 0);
    // InsertHead(&list, 1);
    // InsertHead(&list, 1);
    // InsertHead(&list, 8);
    // InsertHead(&list, 8);
    // InsertHead(&list, 9);
    // InsertHead(&list, 9);
    // InsertHead(&list, 9);

    Trave(&list);

    // while(list.len != 0)
    // {
    //     RemoveByIndex(&list, 0);
    //     Trave(&list);
    // }
    // while (list.len != 0)
    // {
    //     RemoveByIndex(&list, list.len-1);
    //     Trave(&list);
    // }
    // RemoveByIndex(&list, 6);
    // Trave(&list);

    // RemoveByElement(&list, 1);
    // Trave(&list);

    // RemoveByElement(&list, 9);
    // Trave(&list);

    // RemoveByElement(&list, 8);
    // Trave(&list);

    // RemoveByElement(&list, 0);
    // Trave(&list);


    //约瑟夫环问题
    // int count = 1;
    // LNode *TravePoint = list.head;
    // while(list.len != 1)
    // {
    //     if(count == 3)
    //     {
    //         printf("%d is out !\n", TravePoint->data);
    //         LNode *temp = TravePoint->next;
    //         RemoveByElement(&list, TravePoint->data);
    //         TravePoint = temp;
    //         count = 0;
    //     }
    //     else{
    //         TravePoint = TravePoint->next;
    //     }
    //     count++;
    //     printf("%d is alive!\n", TravePoint->data);
    // }

    int k = 3;
    int survivor = Josephus(&list, k);

    printf("Survivor: %d\n", survivor);

    return 0;
}