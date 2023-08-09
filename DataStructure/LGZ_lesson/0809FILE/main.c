#include "StdFile.h"
#include "DoubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>

void Print(ElementType value)
{
    char *content = (char *)value;
    printf("%s\n", content);
}

void freeStr(ElementType value)
{
    free(value);
}

int main(int argc, char *argv[])
{
    // char *content = LoardFromFile("file.txt");
    // if (content != NULL)
    // {
    //     printf("%s\n", content);
    //     free(content);
    // }
    DLlist *list = GetLineFromFile("file.txt");
    Trave(list, Print);

    FreeDLlist(list, freeStr);
    free(list);

    return 0;
}