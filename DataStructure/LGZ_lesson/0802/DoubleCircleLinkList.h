#ifndef __DOUBLECIRCLELINKLIST_H
#define __DOUBLECIRCLELINKLIST_H

#define ElementType int

typedef struct Node
{
    ElementType data;
    struct Node *next;
    struct Node *prev;
} LNode;

typedef struct DoubleCircleLinkList
{
    struct Node *head;
    struct Node *tail;
    int len;
} DCLlist;

int InitDCLlist(DCLlist *list);

void FreeDCLlist(DCLlist *list);

void Trave(DCLlist *list);

void InsertTail(DCLlist *list, ElementType element);

void InsertHead(DCLlist *list, ElementType element);

void InsertIndex(DCLlist *list, ElementType element);

void RemoveByIndex(DCLlist *list, int index);

void RemoveByElement(DCLlist *list, ElementType element);

int FindFirstByElement(DCLlist *list, ElementType element);

int Josephus(DCLlist *list, int k);

#endif