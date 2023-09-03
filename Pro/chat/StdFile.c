#include "StdFile.h"        // 包含自定义的头文件和标准库头文件
#include "DoubleLinkList.h" // 包含双向链表的头文件
#include <stdio.h>          // 包含标准输入输出库的头文件
#include <stdlib.h>         // 包含标准库的头文件
#include <string.h>         // 包含字符串处理库的头文件

#define false 0 // 定义常量 false 为 0
#define true 1  // 定义常量 true 为 1

// 判断文件是否存在
int IsFileExist(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r"); // 尝试以只读方式打开文件
    if (file == NULL)
    {
        return false; // 如果打开失败，返回 false
    }
    else
    {
        fclose(file); // 如果打开成功，关闭文件并返回 true
        return true;
    }

    return 0;
}

// 从文件加载内容到字符串
char *LoardFromFile(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r"); // 以只读方式打开文件
    if (file == NULL)
    {
        printf("file %s open fail!\n", FilePath);
        return NULL; // 如果打开失败，输出错误信息并返回空指针
    }
    else
    {
        printf("file open success!\n"); // 打开成功时输出成功信息
    }

    fseek(file, 0, SEEK_END);  // 定位到文件末尾
    size_t size = ftell(file); // 获取文件大小

    char *content = (char *)malloc(size + 1); // 为内容分配内存空间
    fseek(file, 0, SEEK_SET);                 // 定位回文件开头
    fread(content, size, 1, file);            // 读取文件内容到内存

    fclose(file);   // 关闭文件
    return content; // 返回读取的文件内容
}

// 从字符串中按索引删除字符
void RemoveCharIndex(char *a, int index)
{
    if (index < 0 || index >= strlen(a))
    {
        printf("RemoveIndex invalid place!\n"); // 如果索引无效，输出错误信息
        return;
    }

    for (int i = index; i < strlen(a); i++)
    {
        a[i] = a[i + 1]; // 将字符前移以删除字符
    }
}

// 从字符串中按值删除字符
void RemoveChar(char *a, char element)
{
    int len = strlen(a); // 获取字符串长度
    for (int i = 0; i < len; i++)
    {
        if (a[i] == element)
        {
            RemoveCharIndex(a, i); // 如果找到目标字符，调用按索引删除函数删除
            i--;                   // 需要再次检查当前位置的字符
        }
    }
}

// 从文件中逐行读取内容，并保存到双向链表中
DLlist *GetLineFromFile(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r"); // 以只读方式打开文件
    if (file == NULL)
    {
        printf("file %s open fail!\n", FilePath);
        return NULL; // 如果打开失败，输出错误信息并返回空指针
    }

    DLlist *list = (DLlist *)malloc(sizeof(DLlist)); // 为链表分配内存空间
    InitDLlist(list);                                // 初始化链表

    char ContentTemp[100] = {0}; // 临时存放读取的行内容的数组
    while (fgets(ContentTemp, 100, file) != NULL)
    {
        char *Line = (char *)malloc(strlen(ContentTemp) + 1); // 为行内容分配内存
        strcpy(Line, ContentTemp);                            // 复制行内容到分配的内存
        RemoveChar(Line, '\n');                               // 移除行末的换行符
        InsertTail(list, Line);                               // 将行内容插入链表尾部
    }
    fclose(file); // 关闭文件
    return list;  // 返回保存了每行内容的链表
}

// 将内容写入文件
void WriteToFile(const char *FilePath, void *ptr, size_t size)
{
    FILE *file = fopen(FilePath, "w"); // 以写入方式打开文件
    if (file == NULL)
    {
        printf("writetofile open fail\n");
        return; // 如果打开失败，输出错误信息并返回
    }
    if (fwrite(ptr, size, 1, file) <= 0)
    {
        printf("writetofile fail\n"); // 如果写入失败，输出错误信息
    }

    fclose(file); // 关闭文件
}

// 将链表中的每行内容写入文件
void WriteLineToFile(const char *FilePath, DLlist *list)
{
    FILE *file = fopen(FilePath, "w"); // 以写入方式打开文件
    if (file == NULL)
    {
        printf("writetofile open fail\n");
        return; // 如果打开失败，输出错误信息并返回
    }

    LNode *TravelPoint = list->head; // 遍历链表的指针
    while (TravelPoint != NULL)
    {
        fputs(TravelPoint->data, file);  // 将链表节点数据写入文件
        TravelPoint = TravelPoint->next; // 移动到下一个节点
    }
    fclose(file); // 关闭文件
}

// 将内容追加到文件末尾
void AppendToFile(const char *FilePath, void *ptr, size_t size)
{
    FILE *file = fopen(FilePath, "a"); // 以追加方式打开文件
    if (file == NULL)
    {
        printf("AppendToFile open fail\n");
        return; // 如果打开失败，输出错误信息并返回
    }

    fwrite(ptr, size, 1, file); // 将内容追加到文件末尾
    fclose(file);               // 关闭文件
}

// 复制文件
void CopyFile(const char *SourcePath, const char *TargetPath)
{
    if (IsFileExist(SourcePath) == false) // 检查源文件是否存在
    {
        printf("The source is not exit or read permisson\n");
        return; // 如果不存在或没有读取权限，输出错误信息并返回
    }

    char *fileContent = LoardFromFile(SourcePath); // 从源文件中加载内容

    if (IsFileExist(TargetPath) == true) // 检查目标文件是否存在
    {
        char Target[100] = {0};
        strcpy(Target, TargetPath); // 复制目标文件路径
        char *fileName = strtok(Target, ".");
        char *backName = strtok(NULL, ".");

        char NewPath[100] = {0}; // 新的目标文件路径
        strcpy(NewPath, fileName);
        strcat(NewPath, "_new.");
        strcat(NewPath, backName);        // 构建新的目标文件路径
        if (IsFileExist(NewPath) == true) // 如果新路径已存在
        {
            CopyFile(SourcePath, NewPath); // 递归调用复制文件函数
            return;
        }
        WriteToFile(NewPath, fileContent, strlen(fileContent)); // 将内容写入新的目标文件
        free(fileContent);                                      // 释放内存
        return;
    }
    WriteToFile(TargetPath, fileContent, strlen(fileContent)); // 将内容写入目标文件

    free(fileContent); // 释放内存
}
