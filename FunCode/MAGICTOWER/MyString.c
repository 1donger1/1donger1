#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"

// 返回 MyString 对象的字符串长度
int size(MyString *obj);

// 打印 MyString 对象的字符串
void print(MyString obj);

// 比较两个 MyString 对象的字符串是否相等，返回值：0相等，<0表示 obj1 小于 obj2，>0表示 obj1 大于 obj2
int IsEqual(MyString *obj1, MyString *obj2);

// 检查 MyString 对象是否包含指定的子字符串 s，返回值：1表示包含，0表示不包含
int IsContain(MyString *obj1, const char *s);

// 从 MyString 对象中删除所有的子字符串 s
void RmStr(MyString *obj, const char *s);

// 在 MyString 对象中指定位置 target 处插入子字符串 s
void InsertStr(MyString *obj, const char *s, int target);

// 返回 MyString 对象的字符串长度
int size(MyString *obj)
{
    return strlen(obj->string);
}

// 初始化 MyString 对象，使用给定的字符串 str
void Initialize(MyString *obj, const char *str)
{
    // 计算字符串的长度
    obj->size = strlen(str);
    // 为字符串分配内存空间
    obj->string = (char *)malloc(sizeof(char) * (obj->size + 1));
    if (obj->string == NULL)
    {
        printf("Malloc error\n");
    }

    // 将输入的字符串复制到 MyString 对象中
    strcpy(obj->string, str);

    // 初始化函数指针
    obj->Print = print;
    obj->IsContain = IsContain;
    obj->IsEqual = IsEqual;
    obj->InsertStr = InsertStr;
    obj->RmStr = RmStr;
}

// 打印 MyString 对象的字符串
void print(MyString obj)
{
    printf("%s\n", obj.string);
}

// 比较两个 MyString 对象的字符串是否相等，返回值：0相等，<0表示 obj1 小于 obj2，>0表示 obj1 大于 obj2
int IsEqual(MyString *obj1, MyString *obj2)
{
    int ret = strcmp(obj1->string, obj2->string);
    return ret;
}

// 检查 MyString 对象是否包含指定的子字符串 s，返回值：1表示包含，0表示不包含
int IsContain(MyString *obj1, const char *s)
{
    char *str = strstr(obj1->string, s);
    if (str == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// 从 MyString 对象中删除所有的子字符串 s
void RmStr(MyString *obj, const char *s)
{
    char *Rtmp = strstr(obj->string, s);
    if (Rtmp == NULL)
    {
        return;
    }
    else
    {
        char *str = Rtmp + strlen(s);
        // 将剩余字符串逐个复制到合适的位置，实现删除子字符串
        while (*str != '\0')
        {
            *Rtmp++ = *str++;
        }
        *Rtmp = '\0';
    }
}

// 在 MyString 对象中指定位置 target 处插入子字符串 s
void InsertStr(MyString *dest, const char *s, int target)
{
    if (target < 0 || target > dest->size)
    {
        return;
    }

    // 计算插入后字符串的长度
    int new_str_len = dest->size + strlen(s) + 1;
    // 为插入后字符串分配内存空间
    char *new_str = (char *)malloc(sizeof(char) * new_str_len);
    if (new_str == NULL)
    {
        printf("insertString malloc error\n");
        return;
    }

    // 将原字符串中 target 位置之前的内容复制到新字符串
    strncpy(new_str, dest->string, target);
    // 将需要插入的子字符串复制到新字符串
    strncpy(new_str + target, s, strlen(s));
    // 将原字符串中 target 位置之后的内容复制到新字符串
    strcpy(new_str + target + strlen(s), dest->string + target);

    // 释放原字符串的内存空间
    free(dest->string);
    // 更新 MyString 对象的字符串指针为新字符串
    dest->string = new_str;
    // 更新 MyString 对象的字符串长度
    dest->size = strlen(dest->string);
}

// 释放 MyString 对象的字符串内存空间
void FreeMystring(MyString *obj)
{
    if (obj->string != NULL)
    {
        free(obj->string);
        obj->string = NULL;
    }
}
