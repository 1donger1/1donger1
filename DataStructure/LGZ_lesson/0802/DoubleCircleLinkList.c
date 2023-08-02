#include "DoubleCircleLinkList.h"
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

int InitDCLlist(DCLlist *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return true;
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

void InsertTail(DCLlist *list, ElementType element)
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

        //首尾相连
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }
    list->len++;
}

void InsertHead(DCLlist *list, ElementType element)
{
    InsertTail(list, element);
    if (list->len > 1)
    {
        list->tail = list->tail->prev;
        list->head = list->head->prev;
    }
}

void RemoveByIndex(DCLlist *list, int index)
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
        list->head->prev = list->tail;
        list->tail->next = list->head;
        free(freeNode);
        list->len--;
        return;
    }

    if (index == list->len - 1)
    {
        LNode *freeNode = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = list->head;
        list->head->prev = list->tail;
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

void RemoveByElement(DCLlist *list, ElementType element)
{
    int index = FindFirstByElement(list, element);
    while (index != -1)
    {
        RemoveByIndex(list, index);
        index = FindFirstByElement(list, element);
    }
}

int FindFirstByElement(DCLlist *list, ElementType element)
{
    int count = 0;
    LNode *TravePoint = list->head;
    while (TravePoint != list->tail)
    {
        if (TravePoint->data == element)
        {
            return count;
        }
        count++;
        TravePoint = TravePoint->next;
    }
    if(list->tail != NULL && list->tail->data == element)
    {
        return count;
    }
    return -1;
}

void FreeDLlist(DCLlist *list)
{
    if(list->len == 0)
    {
        return;
    }
    while (list->head != list->tail)
    {
        LNode *freenode = list->head;
        list->head = list->head->next;
        free(freenode);
    }

    free(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

void Trave(DCLlist *list)
{
    if(list->len == 0)
    {
        return;
    }
    printf("Next: ");
    LNode *TravePoint = list->head;
    while (TravePoint != list->tail)
    {
        printf("%d ", TravePoint->data);
        TravePoint = TravePoint->next;
    }
    printf("%d ", list->tail->data);
    printf("\n");

    // printf("Prev: ");
    // TravePoint = list->tail;
    // while (TravePoint != list->head)
    // {
    //     printf("%d ", TravePoint->data);
    //     TravePoint = TravePoint->prev;
    // }
    // printf("%d ", list->head->data);
    // printf("\n");
}


int Josephus(DCLlist *list, int k)
{
    if (list->len == 0 || k <= 0)
    {
        printf("Invalid input!\n");
        return -1;
    }

    int count = 1;
    LNode *TravePoint = list->head;
    while (list->len > 1)
    {
        if (count == k)
        {
            printf("Eliminated: %d\n", TravePoint->data);
            LNode *next = TravePoint->next;
            RemoveByIndex(list, FindFirstByElement(list, TravePoint->data));
            count = 1;
            TravePoint = next;
        }
        else
        {
            count++;
            TravePoint = TravePoint->next;
        }
    }

    int remaining = list->head->data;
    return remaining;
}

