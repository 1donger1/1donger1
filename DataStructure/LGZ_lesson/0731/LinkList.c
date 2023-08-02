#include "LinkList.h"
#define true 1
#define false 0

/// @brief 初始化一个链表
/// 函数通过创建头结点并设置其初始值来初始化一个链表
/// @param list 指向表示链表的LinkList结构体的指针
/// @return 如果初始化成功，则返回true,否则返回false
int InitLinkList(LinkList *list)
{
    list->head = (LNode *)malloc(sizeof(LNode));
    if (list->head == NULL)
    {
        printf("InitLinkList malloc fail!\n");
        return false;
    }
    list->head->data = 0;
    list->head->next = NULL;
    list->len = 0;

    return true;
}

/// @brief 创建一个新的链表节点，并设置节点的数据为给定元素值
/// @param element 要存储在新节点中的元素值
/// @return 返回指向新节点节点的指针。如果内存分配失败，则返回NULL
LNode *CreateNode(ElementType element)
{
    LNode *NewNode = (LNode *)malloc(sizeof(LNode));
    if (NewNode == NULL)
    {
        printf("CreateNode malloc fail!\n");
        return false;
    }
    NewNode->data = element;
    NewNode->next = NULL;
    return NewNode;
}

/// @brief 该函数用于遍历链表，并依次打印每个节点的数据元素。
/// @param list 指向表示链表的LinkList结构体的指针。
void Travel(LinkList *list)
{
    LNode *TravelPoint = list->head->next;

    while (TravelPoint != NULL)
    {
        printf("%d ", TravelPoint->data);
        TravelPoint = TravelPoint->next;
    }
    printf("\n");
}

/// @brief 释放链表中所有节点的内存空间，并将链表的头指针置为空，长度置为0。
/// @param list 指向表示链表的LinkList结构体的指针。
void FreeLinkList(LinkList *list)
{
    LNode *TravelPoint = list->head->next;
    while (TravelPoint != NULL)
    {
        free(list->head);
        list->head = TravelPoint;
        TravelPoint = list->head->next;
    }
    free(list->head);
    list->head = NULL;
    list->len = 0;
}

// 插入
#if 1
/// @brief 尾插法
/// @param list 指向表示链表的LinkList结构体的指针。
/// @param element 要插入的元素值。
void InsertTail(LinkList *list, ElementType element)
{
    LNode *NewNode = CreateNode(element);
    if (NewNode == NULL)
    {
        printf("InsertTail CreateNode Fail!\n");
        return;
    }

    LNode *TravelPoint = list->head;
    while (TravelPoint->next != NULL)
    {
        TravelPoint = TravelPoint->next;
    }
    // 将新插入的节点放在
    TravelPoint->next = NewNode;
    list->len++;
}

/// @brief 头插法
/// @param list 指向表示链表的LinkList结构体的指针。
/// @param element 要插入的元素值。
void InsertHead(LinkList *list, ElementType element)
{
    LNode *NewNode = CreateNode(element);
    if (NewNode == NULL)
    {
        printf("InsertHead CreateNode Fail!\n");
        return;
    }

    NewNode->next = list->head->next;
    list->head->next = NewNode;
    list->len++;
}

/// @brief 在链表的指定位置插入一个新节点，新节点的数据为给定的元素值。
/// @param list 指向表示链表的LinkList结构体的指针。
/// @param element 要插入的元素值。
/// @param index 要插入的位置索引，从0开始计数。如果索引值无效，则插入失败。
void InsertIndex(LinkList *list, ElementType element, int index)
{
    if (index < 0 || index > list->len)
    {
        printf("InsertIndex invaild place!\n");
        return;
    }

    LNode *NewNode = CreateNode(element);
    if (NewNode == NULL)
    {
        printf("InsertHead CreateNode Fail!\n");
        return;
    }

    // 创建一个指针TravelPoint，用于在链表中找到要插入位置的前一个节点
    LNode *TravelPoint = list->head;

    // 找到要插入位置的前一个节点
    // 使用while循环来移动TravelPoint指针，移动的次数为index
    // 这样TravelPoint就指向了要插入位置的前一个节点
    while (index != 0)
    {
        TravelPoint = TravelPoint->next;
        index--;
    }
    NewNode->next = TravelPoint->next;
    TravelPoint->next = NewNode;
    list->len++;
}
#endif

// 删除
#if 1
/// @brief 按索引删除
/// @param list 指向表示链表的LinkList结构体的指针。
/// @param index 要删除的位置索引，从0开始计数。如果索引值无效，则插入失败。
void RemoveByIndex(LinkList *list, int index)
{
    if (index < 0 || index > list->len)
    {
        printf("RemoveByIndex invaild place!\n");
        return;
    }
    LNode *TravelPoint = list->head;
    while (index != 0)
    {
        TravelPoint = TravelPoint->next;
        index--;
    }
    LNode *FreeNode = TravelPoint->next;
    TravelPoint->next = FreeNode->next;
    free(FreeNode);
    list->len--;
}

/// @brief 按值删除
/// @param list 指向表示链表的LinkList结构体的指针
/// @param element 需要删除的值
void RemoveByElement(LinkList *list, ElementType element)
{
    LNode *TravelPoint = list->head;
    while (TravelPoint->next != NULL)
    {
        if (TravelPoint->next->data == element)
        {
            LNode *FreeNode = TravelPoint->next;
            TravelPoint->next = FreeNode->next;
            free(FreeNode);
            list->len--;
        }
        else
        {
            TravelPoint = TravelPoint->next;
        }
    }
}
#endif

// 查找
#if 1
ElementType *FindByIndex(LinkList *list, int index)
{
    if (index < 0 || index >= list->len)
    {
        printf("FindByIndex invaild place!\n");
        return NULL;
    }
    LNode *TravelPoint = list->head;
    while (index != 0)
    {
        TravelPoint = TravelPoint->next;
        index--;
    }
    return &(TravelPoint->next->data);
}

/// @brief 按值查找，并返回其索引下标
/// @param list
/// @param element
/// @return
int *FindByElement(LinkList *list, ElementType element)
{
    int *findvectoer = (int *)malloc(sizeof(int) * (list->len + 1));
    if (findvectoer == NULL)
    {
        printf("findvector malloc fail!\n");
        return NULL;
    }
    LNode *TravelPoint = list->head;
    int count = 0;
    int k = 0;
    while (TravelPoint->next != NULL)
    {
        if (TravelPoint->next->data == element)
        {
            findvectoer[k] = count;

            k++;
        }
        count++;
        TravelPoint = TravelPoint->next;
    }
    findvectoer[k] = -1;
    return findvectoer;
}
#endif

// 修改
#if 1
void SetValueByIndex(LinkList *list, ElementType element, int index)
{
    if (index < 0 || index >= list->len)
    {
        printf("FindByIndex invaild place!\n");
        return;
    }
    LNode *TravelPoint = list->head;

    while (index != 0)
    {
        TravelPoint = TravelPoint->next;
        index--;
    }

    TravelPoint->next->data = element;
}
void SetValueByELement(LinkList *list, ElementType oldValue, ElementType newValue)
{
    // 法一
    //  LNode *TravelPoint = list->head;
    //  while (TravelPoint->next != NULL)
    //  {
    //      if (TravelPoint->next->data == oldValue)
    //      {
    //          TravelPoint->next->data = newValue;
    //      }
    //      TravelPoint = TravelPoint->next;
    //  }
    // 法二
    int *findVector = FindByElement(list, oldValue);
    if (findVector == NULL)
    {
        printf("findVector fail\n");
        return;
    }
    int *temp = findVector;
    while (*temp != -1)
    {
        SetValueByIndex(list, newValue, *temp);
        temp++;
    }

    free(findVector);
}
#endif

// 排序
#if 1
void BubbleSort(LinkList *list)
{
    for (int i = 0; i < list->len - 1; i++) // i是扫描次数
    {
        LNode *TravelPoint = list->head;
        for (int j = 0; j < list->len - i - 1; j++) // j是交换次数
        {
            if (TravelPoint->next->data > TravelPoint->next->next->data)
            {
                LNode *Prev = TravelPoint->next;
                LNode *Next = TravelPoint->next->next;
                // 交换
                Prev->next = Next->next;
                Next->next = Prev;
                TravelPoint->next = Next;
            }

            TravelPoint = TravelPoint->next;
        }
    }
}

void Reverse(LinkList *list)
{
    LNode *prev = NULL;
    LNode *cur = list->head->next;
    LNode *Next = cur->next;

    while (Next != NULL)
    {
        cur->next = prev;
        prev = cur;
        cur = Next;
        Next = cur->next;
    }
    cur->next = prev;
    list->head->next = cur;
}

LNode *Reverse2(LNode *node)
{
    LNode *tail;
    if (node->next != NULL)
    {
        tail = Reverse2(node->next);
        node->next->next = node;
        node->next = NULL;
        return tail;
    }
    return node;
}

/// @brief 归并
/// @param list1
/// @param list2
/// @return
// LinkList *MergeList(LinkList *list1, LinkList *list2)
// {
//     BubbleSort(list1);
//     BubbleSort(list2);

//     LinkList *list3 = (LinkList *)malloc(sizeof(LinkList));
//     if (list3 == NULL)
//     {
//         printf("list3 malloc fail\n");
//         return NULL;
//     }
//     InitLinkList(list3);

//     LNode *TravePoint = list3->head;
//     while (list1->head->next != NULL && list2->head->next != NULL)
//     {
//         if (list1->head->next->data < list2->head->next->data)
//         {
//             TravePoint->next = list1->head->next;
//             list1->head = list1->head->next;
//         }
//         else
//         {
//             TravePoint->next = list2->head->next;
//             list2->head = list2->head->next;
//         }
//         TravePoint = TravePoint->next;
//     }

//     if (list1->head->next != NULL)
//     {
//         TravePoint->next = list1->head->next;
//     }

//     if (list2->head->next != NULL)
//     {
//         TravePoint->next = list2->head->next;
//     }
//     return list3;
// }

LinkList *MergeList(LinkList *list1, LinkList *list2)
{
    BubbleSort(list1);
    BubbleSort(list2);

    LinkList *list3 = (LinkList *)malloc(sizeof(LinkList));
    if (list3 == NULL)
    {
        printf("list3 malloc fail\n");
        return NULL;
    }
    InitLinkList(list3);

    LNode *TravePoint = list3->head;
    LNode *current1 = list1->head->next;
    LNode *current2 = list2->head->next;

    while (current1 != NULL && current2 != NULL)
    {
        if (current1->data < current2->data)
        {
            TravePoint->next = current1;
            current1 = current1->next;
        }
        else
        {
            TravePoint->next = current2;
            current2 = current2->next;
        }
        TravePoint = TravePoint->next;
    }

    if (current1 != NULL)
    {
        TravePoint->next = current1;
    }

    if (current2 != NULL)
    {
        TravePoint->next = current2;
    }
    return list3;
}

#endif