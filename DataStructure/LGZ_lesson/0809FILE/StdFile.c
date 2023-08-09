#include "StdFile.h"
#include "DoubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *LoardFromFile(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r");
    if (file == NULL)
    {
        printf("file %s open fail!\n", FilePath);
        return NULL;
    }
    else
    {
        printf("file open success!\n");
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);

    char *content = (char *)malloc(size + 1);
    fseek(file, 0, SEEK_SET);
    fread(content, size, 1, file);

    fclose(file);
    return content;
}

DLlist *GetLineFromFile(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r");
    if (file == NULL)
    {
        printf("file %s open fail!\n", FilePath);
        return NULL;
    }
    else
    {
        printf("file open success!\n");
    }

    DLlist *list = (DLlist *)malloc(sizeof(DLlist));
    InitDLlist(list);

    char ContentTemp[100] = {0};
    while (fgets(ContentTemp, 100, file) != NULL)
    {
        char *Line = (char *)malloc(strlen(ContentTemp) + 1);
        strcpy(Line, ContentTemp);
        InsertTail(list, Line);
    }
    fclose(file);
    return list;
}
