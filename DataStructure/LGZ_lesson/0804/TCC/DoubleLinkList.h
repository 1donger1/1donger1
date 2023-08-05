#ifndef __DOUBLELINKLIST_H
#define __DOUBLELINKLIST_H

#define ElementType void *

typedef struct Node
{
    ElementType data;
    struct Node *next;
    struct Node *prev;
} LNode;

typedef struct DoubleLinkList
{
    struct Node *head;
    struct Node *tail;
    int len;
} DLlist;

int InitDLlist(DLlist *list);

void FreeDLlist(DLlist *list);

// void Trave(DLlist *list);

void InsertTail(DLlist *list, ElementType element);

void InsertHead(DLlist *list, ElementType element);

void InsertIndex(DLlist *list, ElementType element, int index);//待完善

void RemoveByIndex(DLlist *list, int index);

void RemoveByElement(DLlist *list, ElementType element);

int FindFirstByElement(DLlist *list, ElementType element);

#endif