#include "DoubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    DLlist list;
    InitDLlist(&list);
    for (int i = 0; i < 10; i++)
    {
        // InsertTail(&list, i + 1);
        InsertHead(&list, i);
    }
    Trave(&list);

    InsertIndex(&list, 1, 1);

    // printf("remove!\n");

    // while (list.len != 0)
    // {
        // RemoveByIndex(&list, 0);
        // RemoveByIndex(&list, list.len-1);
        // Trave(&list);
    // }
    // Trave(&list);

    // RemoveByElement(&list, 1);
    Trave(&list);

    FreeDLlist(&list);

    return 0;
}