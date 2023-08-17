#include<stdio.h>
#include<stdlib.h>
#include"DoubleLinkList.h"
#define true 1
#define false 0
int InitDLlist(DLlist *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->len=0;
    return true;
}

struct Node *CreateNode(ElementType element)
{
    struct Node *Newnode = (struct Node *)malloc(sizeof(struct Node));
    if(Newnode == NULL)
    {
        printf("Newnode malloc error!\n");
        return NULL;
    }
    Newnode->next = NULL;
    Newnode->prev = NULL;
    Newnode->data = element;
    return Newnode;
}

void DBInsertTail(DLlist *list,ElementType element)
{
    struct Node *newNode= CreateNode(element);
    if(newNode == NULL)
    {
        printf("InsertTail create error!\n");
        return;
    }  
    if(list->len == 0)
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

void FreeDLlistList(DLlist *list,void (*func)(ElementType))
{
    while (list->head != NULL)
    {
        struct Node * freeNode = list->head;
        list->head = list->head->next;

        func(freeNode->data);
        free(freeNode);
    }
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

void DBTravel(DLlist *list,void (*func)(ElementType,DLlist*),DLlist* GameUserData)
{
    struct Node *TravelPoint = list->head;
    while (TravelPoint != NULL)
    {
        if (func != NULL)
        {
            func(TravelPoint->data,GameUserData);
        }
        
        TravelPoint = TravelPoint->next;
    }
}

void DBInsertHead(DLlist *list, ElementType element)
{
    struct Node *newNode= CreateNode(element);
    if(newNode == NULL)
    {
        printf("InsertTail create error!\n");
        return;
    }  
    if(list->len == 0)
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

void InsertByIndex(DLlist *list, ElementType element, int index)
{
    if(index < 0 ||index>=list->len)
    {
        printf("InsertByIndex invalid index!\n");
        return;
    }
    struct Node *newNode= CreateNode(element);
    if(newNode == NULL)
    {
        printf("InsertTail create error!\n");
        return;
    }  
    struct Node *TravelPoint = list->head; 
    if(index == 0)
    {
        TravelPoint->prev = newNode;
        newNode->next = TravelPoint;
        list->head = newNode;
    }
    else
    {
        while(index != 0)
        {
            TravelPoint = TravelPoint->next;
            index--;
        }
        TravelPoint->prev->next = newNode;
        newNode->prev = TravelPoint->prev;
        newNode->next = TravelPoint;
        TravelPoint->prev = newNode;
    } 
    list->len++;
}

void DBRemoveByIndex(DLlist *list, int index)
{
    if(list->len == 0)
        return;
    if(index < 0 ||index>=list->len)
    {
        printf("RemoveByIndex invalid index!\n");
        return;
    }
    struct Node *TravelPoint = list->head;
    if(index == 0)
    {
        if(list->len == 1 )
        {
            free(list->head);
            list->head = NULL;
            list->tail = NULL;
            list->len = 0;
            return;
        }
        struct Node *freeNode = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(freeNode);
        list->len--;
        return;
    }
    if(index == list->len-1)
    {
        struct Node *freeNode = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(freeNode);
        list->len--;
        return;
    }
    else
    {
        while(index > 0)
        {
            TravelPoint = TravelPoint->next;
            index--;
        } 
        struct Node *PrevNode = TravelPoint->prev;
        struct Node *NextNode = TravelPoint->next;
        PrevNode->next = TravelPoint->next;
        NextNode->prev = TravelPoint->prev;
        free(TravelPoint);
        list->len--;
        return;
    }
}

int FindFirstByElement(DLlist *list, ElementType element)
{
    int count = 0;
    struct Node *TravelPoint = list->head;
    while(TravelPoint!=NULL)
    {
        if(TravelPoint->data == element)
        {
            return count;
        }
        count++;
        TravelPoint=TravelPoint->next;
    }
    return -1;
}

void DBRemoveByElement(DLlist *list, ElementType element)
{
    if(list->len == 0)
        return;
    int index = FindFirstByElement(list,element);
    while( index != -1 )
    {
        DBRemoveByIndex(list,index);
        index=FindFirstByElement(list,element);
    }
}

ElementType *DBFindByIndex(DLlist *list, int index)
{
    if(list->len == 0)
        return NULL;
    if(index < 0 ||index>=list->len)
    {
        printf("InsertByIndex invalid index!\n");
        return NULL;
    }
    struct Node *TravelPoint = list->head;
    while(index != 0)
    {
        TravelPoint = TravelPoint->next;
        index--;
    }

    return &TravelPoint->data;
}

int *DBFindByElement(DLlist *list, ElementType element)
{
    if(list->len == 0)
        return NULL;
    int *findVector=(int *)malloc(sizeof(int)*(list->len+1));
    if(findVector == NULL)
    {
        printf("FindByElement malloc error!\n");
        return NULL;
    }
    struct Node *TravelPoint = list->head;
    int count = 0;
    int k = 0;
    while (TravelPoint!=NULL)
    {
        if(TravelPoint->data == element)
        {
            findVector[count] = k;
            count++;
        }
        k++;
        TravelPoint=TravelPoint->next;
    }
    findVector[count]=-1;

    return findVector;
}

void DBSetValueByIndex(DLlist *list, int index, ElementType element)
{
    if(list->len == 0)
    {
        return;
    }
    if(index < 0 ||index>=list->len)
    {
        printf("SetValueByIndex invalid index!\n");
        return;
    }
    struct Node *TravelPoint = list->head;
    while(index != 0)
    {
        TravelPoint = TravelPoint->next;
        index--;
    }
    TravelPoint->data = element;
    return;
}

void DBSetValueByElement(DLlist *list, ElementType old_element, ElementType new_element)
{
    if(list->len == 0)
    {
        return;
    }
    struct Node *TravelPoint = list->head;
    while(TravelPoint!=NULL)
    {
        if(TravelPoint->data == old_element)
        {
            TravelPoint->data = new_element;
        }
        else
        {
            TravelPoint = TravelPoint->next;
        }   
    }
}



