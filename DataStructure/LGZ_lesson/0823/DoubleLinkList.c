#include "DoubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

int InitDLlist(DLlist *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return 0;
}

LNode *CreateNode(ElementType element)
{
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    if (newNode == NULL)
    {
        printf("CreateNode malloc fail!\n");
        return NULL;
    }

    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = element;
    return newNode;
}

int GetListLen(DLlist *list)
{
    return list->len;
}

void InsertTail(DLlist *list, ElementType element)
{
    LNode *newNode = CreateNode(element);
    if (newNode == NULL)
    {
        printf("InsertTail create fail!\n");
        return;
    }
    if (list->len == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->len++;
}

void InsertHead(DLlist *list, ElementType element)
{
    LNode *newNode = CreateNode(element);
    if (newNode == NULL)
    {
        printf("InsertHead create fail!\n");
        return;
    }
    if (list->len == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
    }
    list->len++;
}

void RemoveByIndex(DLlist *list, int index)
{
    if (index < 0 || index >= list->len)
    {
        printf("RemoveByIndex invaild place!\n");
        return;
    }

    if (index == 0)
    {
        if (list->len == 1)
        {
            free(list->head);
            list->head = NULL;
            list->tail = NULL;
            list->len = 0;
            return;
        }

        LNode *freeNode = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(freeNode);
        list->len--;
        return;
    }

    if (index == list->len - 1)
    {
        LNode *freeNode = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(freeNode);
        list->len--;
        return;
    }

    LNode *TravePoint = list->head;
    while (index > 0)
    {
        TravePoint = TravePoint->next;
        index--;
    }
    LNode *PrevNode = TravePoint->prev;
    LNode *NextNode = TravePoint->next;
    PrevNode->next = TravePoint->next;
    NextNode->prev = TravePoint->prev;

    free(TravePoint);
    list->len--;
}

int FindFirstByElement(DLlist *list, ElementType element)
{
    int count = 0;
    LNode *TravePoint = list->head;
    while (TravePoint != NULL)
    {
        if (TravePoint->data == element)
        {
            return count;
        }
        count++;
        TravePoint = TravePoint->next;
    }
    return -1;
}

void RemoveByElement(DLlist *list, ElementType element)
{
    int index = FindFirstByElement(list, element);
    while(index != -1)
    {
        RemoveByIndex(list, index);
        index = FindFirstByElement(list, element);
    }
}


void FreeDLlist(DLlist *list)
{
    while (list->head != NULL)
    {
        LNode *freenode = list->head;
        list->head = list->head->next;
        free(freenode);
    }

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

// void Trave(DLlist *list)
// {
//     printf("Next: ");
//     LNode *TravePoint = list->head;
//     while (TravePoint != NULL)
//     {
//         printf("%d ", TravePoint->data);
//         TravePoint = TravePoint->next;
//     }
//     printf("\n");

//     printf("Prev: ");
//     TravePoint = list->tail;
//     while (TravePoint != NULL)
//     {
//         printf("%d ", TravePoint->data);
//         TravePoint = TravePoint->prev;
//     }
//     printf("\n");
// }
