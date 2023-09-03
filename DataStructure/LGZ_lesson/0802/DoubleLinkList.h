#ifndef __DOUBLELINKLIST_H
#define __DOUBLELINKLIST_H

#define ElementType int

// 定义双向链表节点结构体
typedef struct Node
{
    ElementType data;  // 节点存储的数据
    struct Node *next; // 指向下一个节点的指针
    struct Node *prev; // 指向前一个节点的指针
} LNode;               // 节点类型的别名

// 定义双向链表结构体
typedef struct DoubleLinkList
{
    LNode *head; // 指向链表头节点的指针
    LNode *tail; // 指向链表尾节点的指针
    int len;           // 链表长度
} DLlist;              // 双向链表类型的别名

int InitDLlist(DLlist *list);

void FreeDLlist(DLlist *list);

void Trave(DLlist *list);

void InsertTail(DLlist *list, ElementType element);

void InsertHead(DLlist *list, ElementType element);

void InsertIndex(DLlist *list, ElementType element, int index);//待完善

void RemoveByIndex(DLlist *list, int index);

void RemoveByElement(DLlist *list, ElementType element);

int FindFirstByElement(DLlist *list, ElementType element);

#endif