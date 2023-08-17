#ifndef __DOUBLELINKLIST_H__
#define __DOUBLELINKLIST_H__
#include "DynamicArray.h"

struct Node
{
    ElementType data;
    struct Node *prev;
    struct Node *next;
};
typedef struct DLlinkList
{
    struct Node *head;
    struct Node *tail;
    int len;
}DLlist;

extern int InitDLlist(DLlist *list);
extern struct Node* CreateNode(ElementType element);
extern void DBInsertTail(DLlist *list,ElementType element);
extern void FreeDLlistList(DLlist *list,void (*func)(ElementType));
extern void DBTravel(DLlist *list,void (*func)(ElementType,DLlist *),DLlist* GameUserData);
extern void DBInsertHead(DLlist *list,ElementType element);
extern void InsertByIndex(DLlist *list,ElementType element,int index);
extern void DBRemoveByIndex(DLlist *list,int index);

int FindFirstByElement(DLlist *list,ElementType element);
extern void DBRemoveByElement(DLlist *list,ElementType element);

extern ElementType *DBFindByIndex(DLlist *list,int index);
extern int *DBFindByElement(DLlist *list,ElementType element);
extern void DBSetValueByIndex(DLlist *list,int index,ElementType element);
extern void DBSetValueByElement(DLlist *list,ElementType old_element,ElementType new_element);

// extern void BubbleSort(DLlist *list);

#endif