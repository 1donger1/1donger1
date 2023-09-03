#include "DoubleLinkList.h" // 包含自定义的双向链表头文件
#include <stdio.h>          // 包含标准输入输出库的头文件
#include <stdlib.h>         // 包含标准库的头文件
#define true 1              // 定义常量 true 为 1
#define false 0             // 定义常量 false 为 0

// 初始化双向链表
int InitDLlist(DLlist *list)
{
    list->head = NULL; // 头节点为空
    list->tail = NULL; // 尾节点为空
    list->len = 0;     // 初始长度为 0
    return 0;
}

// 创建链表节点
LNode *CreateNode(ElementType element)
{
    LNode *newNode = (LNode *)malloc(sizeof(LNode)); // 为新节点分配内存空间
    if (newNode == NULL)
    {
        printf("CreateNode malloc fail!\n"); // 如果分配失败，输出错误信息
        return NULL;
    }

    newNode->next = NULL; // 初始化节点的指针
    newNode->prev = NULL;
    newNode->data = element; // 节点数据赋值
    return newNode;
}

// 获取链表长度
int GetListLen(DLlist *list)
{
    return list->len; // 返回链表长度
}

// 在链表尾部插入节点
void InsertTail(DLlist *list, ElementType element)
{
    LNode *newNode = CreateNode(element); // 创建新节点
    if (newNode == NULL)
    {
        printf("InsertTail create fail!\n"); // 如果创建节点失败，输出错误信息
        return;
    }
    if (list->len == 0) // 如果链表为空
    {
        list->head = newNode; // 头尾节点都指向新节点
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode; // 将新节点连接到尾节点后
        newNode->prev = list->tail;
        list->tail = newNode; // 更新尾节点为新节点
    }
    list->len++; // 链表长度加一
}

// 在链表头部插入节点
void InsertHead(DLlist *list, ElementType element)
{
    LNode *newNode = CreateNode(element); // 创建新节点
    if (newNode == NULL)
    {
        printf("InsertHead create fail!\n"); // 如果创建节点失败，输出错误信息
        return;
    }
    if (list->len == 0) // 如果链表为空
    {
        list->head = newNode; // 头尾节点都指向新节点
        list->tail = newNode;
    }
    else
    {
        list->head->prev = newNode; // 将新节点连接到头节点前
        newNode->next = list->head;
        list->head = newNode; // 更新头节点为新节点
    }
    list->len++; // 链表长度加一
}

// 按索引从链表中删除节点
void RemoveByIndex(DLlist *list, int index)
{
    if (index < 0 || index >= list->len) // 检查索引合法性
    {
        printf("RemoveByIndex invaild place!\n"); // 如果索引无效，输出错误信息
        return;
    }

    if (index == 0) // 如果删除的是头节点
    {
        if (list->len == 1) // 如果链表只有一个节点
        {
            free(list->head); // 释放头节点内存
            list->head = NULL;
            list->tail = NULL;
            list->len = 0;
            return;
        }

        LNode *freeNode = list->head;  // 保存要删除的节点
        list->head = list->head->next; // 更新头节点为下一个节点
        list->head->prev = NULL;       // 更新新头节点的前向指针
        free(freeNode);                // 释放节点内存
        list->len--;                   // 链表长度减一
        return;
    }

    if (index == list->len - 1) // 如果删除的是尾节点
    {
        LNode *freeNode = list->tail;  // 保存要删除的节点
        list->tail = list->tail->prev; // 更新尾节点为前一个节点
        list->tail->next = NULL;       // 更新新尾节点的后向指针
        free(freeNode);                // 释放节点内存
        list->len--;                   // 链表长度减一
        return;
    }

    LNode *TravePoint = list->head; // 用于遍历的指针
    while (index > 0)               // 移动指针到要删除的节点位置
    {
        TravePoint = TravePoint->next;
        index--;
    }
    LNode *PrevNode = TravePoint->prev; // 保存前一个节点
    LNode *NextNode = TravePoint->next; // 保存后一个节点
    PrevNode->next = TravePoint->next;  // 更新前一个节点的后向指针
    NextNode->prev = TravePoint->prev;  // 更新后一个节点的前向指针

    free(TravePoint); // 释放要删除的节点内存
    list->len--;      // 链表长度减一
}

// 按元素查找第一个匹配的节点索引
int FindFirstByElement(DLlist *list, ElementType element)
{
    int count = 0;                  // 记录节点遍历次数
    LNode *TravePoint = list->head; // 用于遍历的指针
    while (TravePoint != NULL)      // 遍历整个链表
    {
        if (TravePoint->data == element) // 如果找到匹配的节点
        {
            return count; // 返回节点索引
        }
        count++;                       // 遍历次数加一
        TravePoint = TravePoint->next; // 移动指针到下一个节点
    }
    return -1; // 如果未找到匹配的节点，返回 -1
}

// 按元素从链表中删除所有匹配的节点
void RemoveByElement(DLlist *list, ElementType element)
{
    int index = FindFirstByElement(list, element); // 查找第一个匹配节点的索引
    while (index != -1)                            // 如果找到匹配的节点
    {
        RemoveByIndex(list, index);                // 调用按索引删除函数删除
        index = FindFirstByElement(list, element); // 继续查找下一个匹配节点的索引
    }
}

// 释放双向链表的内存
void FreeDLlist(DLlist *list)
{
    while (list->head != NULL) // 当链表不为空
    {
        LNode *freenode = list->head;  // 保存头节点
        list->head = list->head->next; // 更新头节点为下一个节点
        free(freenode);                // 释放头节点内存
    }

    list->head = NULL; // 清空链表
    list->tail = NULL;
    list->len = 0;
}

// 遍历链表并对每个节点应用指定函数
void Travel(DLlist *list, void (*func)(ElementType))
{
    LNode *TravePoint = list->head; // 用于遍历的指针
    while (TravePoint != NULL)      // 遍历整个链表
    {
        if (func != NULL) // 如果传入了函数指针
        {
            func(TravePoint->data); // 对当前节点数据应用指定函数
        }
        TravePoint = TravePoint->next; // 移动指针到下一个节点
    }
    printf("\n");
}
