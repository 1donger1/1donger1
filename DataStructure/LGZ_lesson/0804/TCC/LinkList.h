#ifndef __LINKLIST_H
#define __LINKLIST_H_
#include <stdio.h>
#include <stdlib.h>

#define ElementType int

typedef struct Node
{
    ElementType data;
    struct Node *next;
} LNode;

typedef struct LinkList
{
    LNode *head;
    int len;
} LinkList;

int InitLinkList(LinkList *list);

LNode *CreateNode(ElementType element);

void Travel(LinkList *list);

void FreeLinkList(LinkList *list);

void InsertTail(LinkList *list, ElementType element);

void InsertHead(LinkList *list, ElementType element);

void InsertIndex(LinkList *list, ElementType element, int index);

void RemoveByIndex(LinkList *list, int index);

void RemoveByElement(LinkList *list, ElementType element);

ElementType *FindByIndex(LinkList *list, int index);

int *FindByElement(LinkList *list, ElementType element);

void SetValueByIndex(LinkList *list, ElementType element, int index);

void SetValueByELement(LinkList *list, ElementType oldValue, ElementType newValue);

void BubbleSort(LinkList *list);

void Reverse(LinkList *list);

LNode *Reverse2(LNode *node);

LinkList *MergeList(LinkList *list1, LinkList *list2);

#endif