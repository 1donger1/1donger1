#include "LQueue.h" // 包含自定义的队列操作头文件
#include <stdio.h>  // 包含标准输入输出库的头文件
#include <stdlib.h> // 包含标准库的头文件
#define true 1      // 定义常量 true 为 1
#define false 0     // 定义常量 false 为 0

// 初始化链式队列
int InitLQueue(LQueue *lq)
{
    return InitDLlist(&lq->queue); // 调用初始化双向链表函数
}

// 入队操作
void QPush(LQueue *lq, ElementType element)
{
    InsertTail(&lq->queue, element); // 调用双向链表的尾部插入函数
}

// 出队操作
ElementType *LQPop(LQueue *lq)
{
    if (lq->queue.len == 0) // 如果队列为空
    {
        printf("Queue is empty!\n"); // 输出错误信息
        return NULL;
    }
    lq->FrontData = lq->queue.head->data; // 保存队头数据
    RemoveByIndex(&lq->queue, 0);         // 调用双向链表按索引删除函数删除队头节点
    return &lq->FrontData;                // 返回队头数据的指针
}

// 释放队列内存
void FreeQueue(LQueue *lq)
{
    FreeDLlist(&lq->queue); // 调用双向链表的内存释放函数
}

// 判断队列是否为空
int IsQEmpty(LQueue *lq)
{
    if (lq->queue.len == 0) // 如果队列长度为 0
    {
        return true; // 返回 true 表示队列为空
    }
    else
    {
        return false; // 返回 false 表示队列非空
    }
    return 0;
}

// 获取队头节点
LNode *GetFront(LQueue *lq)
{
    return lq->queue.head; // 返回队列的头节点指针
}

// 获取队列长度
int GetLQueueLen(LQueue *lq)
{
    return lq->queue.len; // 返回队列的长度
}
