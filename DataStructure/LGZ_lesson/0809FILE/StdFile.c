#include "StdFile.h"
#include "DoubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1

int IsFileExist(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r");
    if (file == NULL)
    {
        return false;
    }
    else
    {
        fclose(file);
        return true;
    }

    return 0;
}

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

// 按下标删除
void RemoveCharIndex(char *a, int index)
{
    if (index < 0 || index >= strlen(a))
    {
        printf("RemoveIndex invalid place!\n");
        return;
    }

    for (int i = index; i < strlen(a); i++)
    {
        a[i] = a[i + 1];
    }
}

// 按值删除
void RemoveChar(char *a, char element)
{
    int len = strlen(a);
    for (int i = 0; i < len; i++)
    {
        if (a[i] == element)
        {
            RemoveCharIndex(a, i);
            i--;
        }
    }
}

DLlist *GetLineFromFile(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r");
    if (file == NULL)
    {
        printf("file %s open fail!\n", FilePath);
        return NULL;
    }
    // else
    // {
    //     printf("file open success!\n");
    // }

    DLlist *list = (DLlist *)malloc(sizeof(DLlist));
    InitDLlist(list);

    char ContentTemp[100] = {0};
    while (fgets(ContentTemp, 100, file) != NULL)
    {
        // ContentTemp[strlen(ContentTemp) - 1] = '\0';
        char *Line = (char *)malloc(strlen(ContentTemp)+1);
        strcpy(Line, ContentTemp);
        RemoveChar(Line, '\n');
        InsertTail(list, Line);
    }
    fclose(file);
    return list;
}

void WriteToFile(const char *FilePath, void *ptr, size_t size)
{
    FILE *file = fopen(FilePath, "w");
    if (file == NULL)
    {
        printf("writetofile open fail\n");
        return;
    }
    if (fwrite(ptr, size, 1, file) <= 0)
    {
        printf("writetofile fail\n");
    }

    fclose(file);
}

void WriteLineToFile(const char *FilePath, DLlist *list)
{
    FILE *file = fopen(FilePath, "w");
    if (file == NULL)
    {
        printf("writetofile open fail\n");
        return;
    }

    LNode *TravelPoint = list->head;
    while (TravelPoint != NULL)
    {
        fputs(TravelPoint->data, file);
        TravelPoint = TravelPoint->next;
    }
    fclose(file);
}

void AppendToFile(const char *FilePath, void *ptr, size_t size)
{
    FILE *file = fopen(FilePath, "a");
    if (file == NULL)
    {
        printf("AppendToFile open fail\n");
        return;
    }

    fwrite(ptr, size, 1, file);
    fclose(file);
}

void CopyFile(const char *SourcePath, const char *TargetPath)
{
    if (IsFileExist(SourcePath) == false)
    {
        printf("The source is not exit or read permisson\n");
        return;
    }

    char *fileContent = LoardFromFile(SourcePath);

    if (IsFileExist(TargetPath) == true)
    {
        char Target[100] = {0};
        strcpy(Target, TargetPath);
        char *fileName = strtok(Target, ".");
        char *backName = strtok(NULL, ".");

        char NewPath[100] = {0};
        strcpy(NewPath, fileName);
        strcat(NewPath, "_new.");
        strcat(NewPath, backName);
        if (IsFileExist(NewPath) == true)
        {
            CopyFile(SourcePath, NewPath);
            return;
        }
        WriteToFile(NewPath, fileContent, strlen(fileContent));
        free(fileContent);
        return;
    }
    WriteToFile(TargetPath, fileContent, strlen(fileContent));

    free(fileContent);
}
