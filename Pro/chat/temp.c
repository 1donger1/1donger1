/**************************DoubleLinkList.h******************************/
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
void Travel(DLlist *list, void (*func)(ElementType));

int GetListLen(DLlist *list);

void InsertTail(DLlist *list, ElementType element);

void InsertHead(DLlist *list, ElementType element);

void RemoveByIndex(DLlist *list, int index);

void RemoveByElement(DLlist *list, ElementType element);

int FindFirstByElement(DLlist *list, ElementType element);

#endif

/**************************DoubleLinkList.c******************************/
#include "DoubleLinkList.h" // 包含自定义的双向链表头文件
#include <stdio.h>          // 包含标准输入输出库的头文件
#include <stdlib.h>         // 包含标准库的头文件
#define true 1              // 定义常量 true 为 1
#define false 0             // 定义常量 false 为 0

// 初始化双向链表
int InitDLlist(DLlist *list)
{
    list->head = NULL; // 头节点为空
    list->tail = NULL; // 尾节点为空
    list->len = 0;     // 初始长度为 0
    return 0;
}

// 创建链表节点
LNode *CreateNode(ElementType element)
{
    LNode *newNode = (LNode *)malloc(sizeof(LNode)); // 为新节点分配内存空间
    if (newNode == NULL)
    {
        printf("CreateNode malloc fail!\n"); // 如果分配失败，输出错误信息
        return NULL;
    }

    newNode->next = NULL; // 初始化节点的指针
    newNode->prev = NULL;
    newNode->data = element; // 节点数据赋值
    return newNode;
}

// 获取链表长度
int GetListLen(DLlist *list)
{
    return list->len; // 返回链表长度
}

// 在链表尾部插入节点
void InsertTail(DLlist *list, ElementType element)
{
    LNode *newNode = CreateNode(element); // 创建新节点
    if (newNode == NULL)
    {
        printf("InsertTail create fail!\n"); // 如果创建节点失败，输出错误信息
        return;
    }
    if (list->len == 0) // 如果链表为空
    {
        list->head = newNode; // 头尾节点都指向新节点
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode; // 将新节点连接到尾节点后
        newNode->prev = list->tail;
        list->tail = newNode; // 更新尾节点为新节点
    }
    list->len++; // 链表长度加一
}

// 在链表头部插入节点
void InsertHead(DLlist *list, ElementType element)
{
    LNode *newNode = CreateNode(element); // 创建新节点
    if (newNode == NULL)
    {
        printf("InsertHead create fail!\n"); // 如果创建节点失败，输出错误信息
        return;
    }
    if (list->len == 0) // 如果链表为空
    {
        list->head = newNode; // 头尾节点都指向新节点
        list->tail = newNode;
    }
    else
    {
        list->head->prev = newNode; // 将新节点连接到头节点前
        newNode->next = list->head;
        list->head = newNode; // 更新头节点为新节点
    }
    list->len++; // 链表长度加一
}

// 按索引从链表中删除节点
void RemoveByIndex(DLlist *list, int index)
{
    if (index < 0 || index >= list->len) // 检查索引合法性
    {
        printf("RemoveByIndex invaild place!\n"); // 如果索引无效，输出错误信息
        return;
    }

    if (index == 0) // 如果删除的是头节点
    {
        if (list->len == 1) // 如果链表只有一个节点
        {
            free(list->head); // 释放头节点内存
            list->head = NULL;
            list->tail = NULL;
            list->len = 0;
            return;
        }

        LNode *freeNode = list->head;  // 保存要删除的节点
        list->head = list->head->next; // 更新头节点为下一个节点
        list->head->prev = NULL;       // 更新新头节点的前向指针
        free(freeNode);                // 释放节点内存
        list->len--;                   // 链表长度减一
        return;
    }

    if (index == list->len - 1) // 如果删除的是尾节点
    {
        LNode *freeNode = list->tail;  // 保存要删除的节点
        list->tail = list->tail->prev; // 更新尾节点为前一个节点
        list->tail->next = NULL;       // 更新新尾节点的后向指针
        free(freeNode);                // 释放节点内存
        list->len--;                   // 链表长度减一
        return;
    }

    LNode *TravePoint = list->head; // 用于遍历的指针
    while (index > 0)               // 移动指针到要删除的节点位置
    {
        TravePoint = TravePoint->next;
        index--;
    }
    LNode *PrevNode = TravePoint->prev; // 保存前一个节点
    LNode *NextNode = TravePoint->next; // 保存后一个节点
    PrevNode->next = TravePoint->next;  // 更新前一个节点的后向指针
    NextNode->prev = TravePoint->prev;  // 更新后一个节点的前向指针

    free(TravePoint); // 释放要删除的节点内存
    list->len--;      // 链表长度减一
}

// 按元素查找第一个匹配的节点索引
int FindFirstByElement(DLlist *list, ElementType element)
{
    int count = 0;                  // 记录节点遍历次数
    LNode *TravePoint = list->head; // 用于遍历的指针
    while (TravePoint != NULL)      // 遍历整个链表
    {
        if (TravePoint->data == element) // 如果找到匹配的节点
        {
            return count; // 返回节点索引
        }
        count++;                       // 遍历次数加一
        TravePoint = TravePoint->next; // 移动指针到下一个节点
    }
    return -1; // 如果未找到匹配的节点，返回 -1
}

// 按元素从链表中删除所有匹配的节点
void RemoveByElement(DLlist *list, ElementType element)
{
    int index = FindFirstByElement(list, element); // 查找第一个匹配节点的索引
    while (index != -1)                            // 如果找到匹配的节点
    {
        RemoveByIndex(list, index);                // 调用按索引删除函数删除
        index = FindFirstByElement(list, element); // 继续查找下一个匹配节点的索引
    }
}

// 释放双向链表的内存
void FreeDLlist(DLlist *list)
{
    while (list->head != NULL) // 当链表不为空
    {
        LNode *freenode = list->head;  // 保存头节点
        list->head = list->head->next; // 更新头节点为下一个节点
        free(freenode);                // 释放头节点内存
    }

    list->head = NULL; // 清空链表
    list->tail = NULL;
    list->len = 0;
}

// 遍历链表并对每个节点应用指定函数
void Travel(DLlist *list, void (*func)(ElementType))
{
    LNode *TravePoint = list->head; // 用于遍历的指针
    while (TravePoint != NULL)      // 遍历整个链表
    {
        if (func != NULL) // 如果传入了函数指针
        {
            func(TravePoint->data); // 对当前节点数据应用指定函数
        }
        TravePoint = TravePoint->next; // 移动指针到下一个节点
    }
    printf("\n");
}

/*********************StdFile.h*********************/
#ifndef __STDFILE_H_
#define __STDFILE_H_
#include "DoubleLinkList.h"
#include <stddef.h>

int IsFileExist(const char *FilePath);

char *LoardFromFile(const char *FilePath);

DLlist *GetLineFromFile(const char *FilePath);

void WriteToFile(const char *FilePath, void *ptr, size_t size);

void WriteLineToFile(const char *FilePath, DLlist *list);

void AppendToFile(const char *FilePath, void *ptr, size_t size);

void CopyFile(const char *SourcePath, const char *TargetPath);

#endif

/*********************StdFile.c*********************/
#include "StdFile.h"        // 包含自定义的头文件和标准库头文件
#include "DoubleLinkList.h" // 包含双向链表的头文件
#include <stdio.h>          // 包含标准输入输出库的头文件
#include <stdlib.h>         // 包含标准库的头文件
#include <string.h>         // 包含字符串处理库的头文件

#define false 0 // 定义常量 false 为 0
#define true 1  // 定义常量 true 为 1

// 判断文件是否存在
int IsFileExist(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r"); // 尝试以只读方式打开文件
    if (file == NULL)
    {
        return false; // 如果打开失败，返回 false
    }
    else
    {
        fclose(file); // 如果打开成功，关闭文件并返回 true
        return true;
    }

    return 0;
}

// 从文件加载内容到字符串
char *LoardFromFile(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r"); // 以只读方式打开文件
    if (file == NULL)
    {
        printf("file %s open fail!\n", FilePath);
        return NULL; // 如果打开失败，输出错误信息并返回空指针
    }
    else
    {
        printf("file open success!\n"); // 打开成功时输出成功信息
    }

    fseek(file, 0, SEEK_END);  // 定位到文件末尾
    size_t size = ftell(file); // 获取文件大小

    char *content = (char *)malloc(size + 1); // 为内容分配内存空间
    fseek(file, 0, SEEK_SET);                 // 定位回文件开头
    fread(content, size, 1, file);            // 读取文件内容到内存

    fclose(file);   // 关闭文件
    return content; // 返回读取的文件内容
}

// 从字符串中按索引删除字符
void RemoveCharIndex(char *a, int index)
{
    if (index < 0 || index >= strlen(a))
    {
        printf("RemoveIndex invalid place!\n"); // 如果索引无效，输出错误信息
        return;
    }

    for (int i = index; i < strlen(a); i++)
    {
        a[i] = a[i + 1]; // 将字符前移以删除字符
    }
}

// 从字符串中按值删除字符
void RemoveChar(char *a, char element)
{
    int len = strlen(a); // 获取字符串长度
    for (int i = 0; i < len; i++)
    {
        if (a[i] == element)
        {
            RemoveCharIndex(a, i); // 如果找到目标字符，调用按索引删除函数删除
            i--;                   // 需要再次检查当前位置的字符
        }
    }
}

// 从文件中逐行读取内容，并保存到双向链表中
DLlist *GetLineFromFile(const char *FilePath)
{
    FILE *file = fopen(FilePath, "r"); // 以只读方式打开文件
    if (file == NULL)
    {
        printf("file %s open fail!\n", FilePath);
        return NULL; // 如果打开失败，输出错误信息并返回空指针
    }

    DLlist *list = (DLlist *)malloc(sizeof(DLlist)); // 为链表分配内存空间
    InitDLlist(list);                                // 初始化链表

    char ContentTemp[100] = {0}; // 临时存放读取的行内容的数组
    while (fgets(ContentTemp, 100, file) != NULL)
    {
        char *Line = (char *)malloc(strlen(ContentTemp) + 1); // 为行内容分配内存
        strcpy(Line, ContentTemp);                            // 复制行内容到分配的内存
        RemoveChar(Line, '\n');                               // 移除行末的换行符
        InsertTail(list, Line);                               // 将行内容插入链表尾部
    }
    fclose(file); // 关闭文件
    return list;  // 返回保存了每行内容的链表
}

// 将内容写入文件
void WriteToFile(const char *FilePath, void *ptr, size_t size)
{
    FILE *file = fopen(FilePath, "w"); // 以写入方式打开文件
    if (file == NULL)
    {
        printf("writetofile open fail\n");
        return; // 如果打开失败，输出错误信息并返回
    }
    if (fwrite(ptr, size, 1, file) <= 0)
    {
        printf("writetofile fail\n"); // 如果写入失败，输出错误信息
    }

    fclose(file); // 关闭文件
}

// 将链表中的每行内容写入文件
void WriteLineToFile(const char *FilePath, DLlist *list)
{
    FILE *file = fopen(FilePath, "w"); // 以写入方式打开文件
    if (file == NULL)
    {
        printf("writetofile open fail\n");
        return; // 如果打开失败，输出错误信息并返回
    }

    LNode *TravelPoint = list->head; // 遍历链表的指针
    while (TravelPoint != NULL)
    {
        fputs(TravelPoint->data, file);  // 将链表节点数据写入文件
        TravelPoint = TravelPoint->next; // 移动到下一个节点
    }
    fclose(file); // 关闭文件
}

// 将内容追加到文件末尾
void AppendToFile(const char *FilePath, void *ptr, size_t size)
{
    FILE *file = fopen(FilePath, "a"); // 以追加方式打开文件
    if (file == NULL)
    {
        printf("AppendToFile open fail\n");
        return; // 如果打开失败，输出错误信息并返回
    }

    fwrite(ptr, size, 1, file); // 将内容追加到文件末尾
    fclose(file);               // 关闭文件
}

// 复制文件
void CopyFile(const char *SourcePath, const char *TargetPath)
{
    if (IsFileExist(SourcePath) == false) // 检查源文件是否存在
    {
        printf("The source is not exit or read permisson\n");
        return; // 如果不存在或没有读取权限，输出错误信息并返回
    }

    char *fileContent = LoardFromFile(SourcePath); // 从源文件中加载内容

    if (IsFileExist(TargetPath) == true) // 检查目标文件是否存在
    {
        char Target[100] = {0};
        strcpy(Target, TargetPath); // 复制目标文件路径
        char *fileName = strtok(Target, ".");
        char *backName = strtok(NULL, ".");

        char NewPath[100] = {0}; // 新的目标文件路径
        strcpy(NewPath, fileName);
        strcat(NewPath, "_new.");
        strcat(NewPath, backName);        // 构建新的目标文件路径
        if (IsFileExist(NewPath) == true) // 如果新路径已存在
        {
            CopyFile(SourcePath, NewPath); // 递归调用复制文件函数
            return;
        }
        WriteToFile(NewPath, fileContent, strlen(fileContent)); // 将内容写入新的目标文件
        free(fileContent);                                      // 释放内存
        return;
    }
    WriteToFile(TargetPath, fileContent, strlen(fileContent)); // 将内容写入目标文件

    free(fileContent); // 释放内存
}

/*************************StdThread.h*******************************/
#ifndef __STDTHREAD_H_
#define __STDTHREAD_H_

struct StdThread;
typedef struct StdThread Thread;

Thread *InitThread(void *(*func)(void *), void *arg);

unsigned long int GetThreadId(Thread *t);

void *JoinThread(Thread *t);

void DetachTherad(Thread *t);

void CancelThread(Thread *t);

void ClearThread(Thread *t);

#endif
/*************************StdThread.c*******************************/
#include "StdThread.h" // 包含自定义的线程操作头文件
#include <stdio.h>     // 包含标准输入输出库的头文件
#include <stdlib.h>    // 包含标准库的头文件
#include <pthread.h>   // 包含 POSIX 线程库的头文件

// 定义线程结构体
struct StdThread
{
    pthread_t threadID; // 线程 ID
};

// 初始化线程
Thread *InitThread(void *(*func)(void *), void *arg)
{
    Thread *t = (Thread *)malloc(sizeof(Thread)); // 为线程结构体分配内存
    if (t == NULL)
    {
        printf("InitThread malloc fail\n"); // 如果分配失败，输出错误信息
        return NULL;
    }
    if (pthread_create(&t->threadID, NULL, func, arg) != 0) // 创建线程
    {
        perror("InitThread pthread_create\n"); // 如果创建失败，输出错误信息
        free(t);                               // 释放内存
        return NULL;
    }
    return t; // 返回初始化的线程
}

// 等待线程结束并获取返回值
void *JoinThread(Thread *t)
{
    void *value = NULL;                // 用于保存返回值的指针
    pthread_join(t->threadID, &value); // 等待线程结束并获取返回值
    return value;                      // 返回线程的返回值
}

// 分离线程
void DetachTherad(Thread *t)
{
    if (pthread_detach(t->threadID) != 0) // 分离线程
    {
        perror("fail to DetachTherad\n"); // 如果分离失败，输出错误信息
        return;
    }
}

// 取消线程
void CancelThread(Thread *t)
{
    if (pthread_cancel(t->threadID) != 0) // 取消线程
    {
        perror("fail to CancelThread"); // 如果取消失败，输出错误信息
        return;
    }
}

// 清理线程资源
void ClearThread(Thread *t)
{
    free(t); // 释放线程结构体内存
}

// 获取线程ID
unsigned long int GetThreadId(Thread *t)
{
    return t->threadID; // 返回线程的ID
}

/*******************LQueue.h**************************/
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "DoubleLinkList.h"

typedef struct LinkQueue
{
    DLlist queue;
    ElementType FrontData;
} LQueue;

int InitLQueue(LQueue *lq);

void QPush(LQueue *lq, ElementType element);

ElementType *LQPop(LQueue *lq);

int GetLQueueLen(LQueue *lq);

void FreeQueue(LQueue *lq);

int IsQEmpty(LQueue *lq);

LNode *GetFront(LQueue *lq);

#endif
/*******************LQueue.c**************************/
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

/*******************LQueue.h**************************/
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "DoubleLinkList.h"

typedef struct LinkQueue
{
    DLlist queue;
    ElementType FrontData;
} LQueue;

int InitLQueue(LQueue *lq);

void QPush(LQueue *lq, ElementType element);

ElementType *LQPop(LQueue *lq);

int GetLQueueLen(LQueue *lq);

void FreeQueue(LQueue *lq);

int IsQEmpty(LQueue *lq);

LNode *GetFront(LQueue *lq);

#endif
/*******************LQueue.c**************************/
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

/******************Stdtcp.h*************************/
#ifndef _STDTCP_H_
#define _STDTCP_H_
#include <stddef.h>

struct TcpServer;
typedef struct TcpServer TcpS;

TcpS *InitTcpServer(const char *ip, short int port);

int TcpServerAccept(TcpS *s);

void TcpServerSend(int ClientSock, void *ptr, size_t size);

void TcpServerRecv(int ClientSock, void *ptr, size_t size);

void ClearTcpServer(TcpS *s);

/*******************************Client***********************************/
struct TcpClient;
typedef struct TcpClient TcpC;

TcpC *InitTcpClient(const char *ServerIp, short int ServerPort);

void TcpClientSend(TcpC *c, void *ptr, size_t size);

void TcpClientRecv(TcpC *c, void *ptr, size_t size);

void ClearTcpClient(TcpC *c);
#endif

/******************Stdtcp.c*************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Stdtcp.h"

struct TcpServer
{
    int sock;
};

TcpS *InitTcpServer(const char *ip, short int port)
{
    TcpS *s = (TcpS *)malloc(sizeof(TcpS));
    if (s == NULL)
    {
        perror("fail to InitTcpServer malloc\n");
        return NULL;
    }

    s->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (s->sock < 0)
    {
        perror("fail to socket\n");
        free(s);
        return NULL;
    }

    int on = 1;
    if (setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0)
    {
        perror("fail to setsockpot\n");
        free(s);
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(s->sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        free(s);
        return NULL;
    }

    if (listen(s->sock, 10) < 0)
    {
        perror("fail to listen\n");
        free(s);
        return NULL;
    }

    return s;
}

int TcpServerAccept(TcpS *s)
{
    struct sockaddr_in addr;
    socklen_t len;
    int acceptSock = 0;
    if ((acceptSock = accept(s->sock, (struct sockaddr *)&addr, &len)) < 0)
    {
        perror("fail to TcpServerAccept accept\n");
        return -1;
    }
    return acceptSock;
}

void TcpServerSend(int ClientSock, void *ptr, size_t size)
{
    if (send(ClientSock, ptr, size, 0) < 0)
    {
        perror("fail to TcpServerSend send\n");
        return;
    }
}

void TcpServerRecv(int ClientSock, void *ptr, size_t size)
{
    if (recv(ClientSock, ptr, size, 0) < 0)
    {
        perror("fail to TcpServerRecv recv\n");
        return;
    }
}

void ClearTcpServer(TcpS *s)
{
    close(s->sock);
    free(s);
}

/*******************************Client***********************************/

struct TcpClient
{
    int sock;
};

TcpC *InitTcpClient(const char *ServerIp, short int ServerPort)
{
    TcpC *c = (TcpC *)malloc(sizeof(TcpC));
    if (c == NULL)
    {
        perror("fail to InitTcpClient malloc\n");
        return NULL;
    }

    c->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (c->sock < 0)
    {
        perror("fail to InitTcpClient sock\n");
        free(c);
        return NULL;
    }

    struct sockaddr_in ServerAddr;
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(ServerPort);
    ServerAddr.sin_addr.s_addr = inet_addr(ServerIp);
    if (connect(c->sock, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) < 0)
    {
        perror("fail to connet\n");
        free(c);
        return NULL;
    }
    return c;
}

void TcpClientSend(TcpC *c, void *ptr, size_t size)
{
    if (send(c->sock, ptr, size, 0) < 0)
    {
        perror("fail to TcpClientSend send\n");
        return;
    }
}

void TcpClientRecv(TcpC *c, void *ptr, size_t size)
{
    if (recv(c->sock, ptr, size, 0) < 0)
    {
        perror("fail to TcpClientRecv recv\n");
        return;
    }
}

void ClearTcpClient(TcpC *c)
{
    close(c->sock);
    free(c);
}

/******************ThreadPool.h*********************/
#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

typedef struct ThreadPool ThreadP;

ThreadP *InitThreadPool(int max_thrd_num, int min_thrd_num, int max_queue_num);

void ThreadP_AddTask(ThreadP *p, void *(*func)(void *), void *arg);

void DestoryThreadPool(ThreadP *p);

#endif

/******************ThreadPool.c*********************/
#include <stdio.h>   // 包含标准输入输出库的头文件
#include <stdlib.h>  // 包含标准库的头文件
#include <string.h>  // 包含字符串库的头文件
#include <pthread.h> // 包含线程库的头文件
#include <unistd.h>  // 包含 POSIX 系统调用库的头文件

#include "DoubleLinkList.h" // 包含自定义的双向链表头文件
#include "StdThread.h"      // 包含自定义的线程操作头文件
#include "ThreadPool.h"     // 包含自定义的线程池头文件
#include "LQueue.h"         // 包含自定义的队列头文件

#define true 1
#define false 0
#define Sleep_Time 10 // 线程休眠时间

typedef struct Task
{
    void *(*function)(void *);
    void *arg;
} task;

// 创建任务
task *CreateTask(void *(*func)(void *), void *arg)
{
    task *t = (task *)malloc(sizeof(task)); // 为任务分配内存
    if (t == NULL)
    {
        printf("fail to CreateTask malloc\n"); // 如果分配失败，输出错误信息
        return NULL;
    }
    t->function = func;
    t->arg = arg;
    return t;
}

// 释放任务
void FreeTask(task *t)
{
    free(t);
}

struct ThreadPool
{
    DLlist threads;    // 线程列表
    LQueue task_queue; // 任务队列

    int min_thrd_num;   // 最小线程数
    int max_thrd_num;   // 最大线程数
    int max_queue_size; // 最大队列大小
    int busy_thrd_num;  // 忙碌线程数
    int exit_thrd_num;  // 退出线程数

    pthread_mutex_t pool_mutex;      // 线程池互斥锁
    pthread_mutex_t busy_thrd_mutex; // 忙碌线程互斥锁
    pthread_cond_t queue_not_empty;  // 队列非空条件变量
    pthread_cond_t queue_not_full;   // 队列非满条件变量

    Thread *admin_thread; // 管理线程

    int shutdown; // 线程池关闭标志
};

// 线程工作函数
void *thread_worker(void *arg)
{
    ThreadP *p = (ThreadP *)arg;
    while (1)
    {
        pthread_mutex_lock(&p->pool_mutex);

        while (IsQEmpty(&p->task_queue) == true && p->shutdown == false)
        {
            pthread_cond_wait(&p->queue_not_empty, &p->pool_mutex);

            if (p->exit_thrd_num > 0)
            {
                p->exit_thrd_num--;

                LNode *TravelPoint = p->threads.head;
                while (TravelPoint != NULL)
                {
                    Thread *t = (Thread *)TravelPoint->data;
                    if (GetThreadId(t) == pthread_self())
                    {
                        RemoveByElement(&p->threads, t);
                        break;
                    }
                    TravelPoint = TravelPoint->next;
                }
                pthread_mutex_unlock(&p->pool_mutex);
                pthread_exit(NULL);
            }
        }

        if (p->shutdown == true)
        {
            pthread_mutex_unlock(&p->pool_mutex);
            pthread_exit(NULL);
        }
        task *tk = (task *)(*LQPop(&p->task_queue));
        pthread_mutex_unlock(&p->pool_mutex);

        pthread_cond_broadcast(&p->queue_not_full);

        pthread_mutex_lock(&p->busy_thrd_mutex);
        p->busy_thrd_num++;
        pthread_mutex_unlock(&p->busy_thrd_mutex);

        tk->function(tk->arg);

        pthread_mutex_lock(&p->busy_thrd_mutex);
        p->busy_thrd_num--;
        pthread_mutex_unlock(&p->busy_thrd_mutex);

        FreeTask(tk);
    }
}

// 线程管理函数
void *thread_manager(void *arg)
{
    ThreadP *p = (ThreadP *)arg;
    while (p->shutdown != true)
    {
        sleep(Sleep_Time);
        pthread_mutex_lock(&p->pool_mutex);

        // 创建线程
        int queueLen = GetLQueueLen(&p->task_queue);
        int thread_num = GetListLen(&p->threads);
        if (p->busy_thrd_num < GetLQueueLen(&p->task_queue) && GetListLen(&p->threads) < p->max_thrd_num)
        {
            int add = (queueLen / 2) > (p->max_thrd_num - thread_num) ? (p->max_thrd_num - thread_num) : (queueLen / 2);
            for (int i = 0; i < add; i++)
            {
                Thread *t = InitThread(thread_worker, p);
                InsertTail(&p->threads, t);
            }
        }

        // 销毁线程
        if (thread_num > p->busy_thrd_num * 2 && thread_num > p->min_thrd_num)
        {
            int minus_thrd_num = (thread_num - p->busy_thrd_num) / 2;
            int minus = minus_thrd_num > (thread_num - p->min_thrd_num) ? (thread_num - p->min_thrd_num) : minus_thrd_num;

            p->exit_thrd_num = minus;
            pthread_mutex_unlock(&p->pool_mutex);
            for (int i = 0; i < minus; i++)
            {
                pthread_cond_broadcast(&p->queue_not_empty);
            }
            continue;
        }

        pthread_mutex_unlock(&p->pool_mutex);
    }
    pthread_exit(NULL); // 退出管理线程
}

// 初始化线程池
ThreadP *InitThreadPool(int max_thrd_num, int min_thrd_num, int max_queue_num)
{
    ThreadP *p = (ThreadP *)malloc(sizeof(ThreadP)); // 为线程池分配内存
    if (p == NULL)
    {
        printf("fail to InitThreadPool\n"); // 如果分配失败，输出错误信息
        return NULL;
    }

    InitDLlist(&p->threads);    // 初始化线程列表
    InitLQueue(&p->task_queue); // 初始化任务队列

    p->max_thrd_num = max_thrd_num;    // 设置最大线程数
    p->min_thrd_num = min_thrd_num;    // 设置最小线程数
    p->max_queue_size = max_queue_num; // 设置最大队列大小
    p->busy_thrd_num = 0;              // 忙碌线程数初始为0
    p->exit_thrd_num = 0;              // 退出线程数初始为0

    pthread_mutex_init(&p->pool_mutex, NULL);      // 初始化线程池互斥锁
    pthread_mutex_init(&p->busy_thrd_mutex, NULL); // 初始化忙碌线程互斥锁
    pthread_cond_init(&p->queue_not_empty, NULL);  // 初始化队列非空条件变量
    pthread_cond_init(&p->queue_not_full, NULL);   // 初始化队列非满条件变量

    p->shutdown = false; // 初始化关闭标志为false

    for (int i = 0; i < p->max_thrd_num; i++) // 创建初始线程
    {
        Thread *t = InitThread(thread_worker, p);
        InsertTail(&p->threads, t);
    }

    p->admin_thread = InitThread(thread_manager, p); // 创建管理线程
    return p;
}

// 向线程池添加任务
void ThreadP_AddTask(ThreadP *p, void *(*func)(void *), void *arg)
{
    pthread_mutex_lock(&p->pool_mutex);
    while (IsQEmpty(&p->task_queue) == p->max_queue_size) // 如果任务队列已满
    {
        pthread_cond_wait(&p->queue_not_full, &p->pool_mutex); // 等待队列非满条件
    }
    if (p->shutdown == true) // 如果线程池已关闭
    {
        pthread_mutex_unlock(&p->pool_mutex); // 解锁并返回
        return;
    }
    QPush(&p->task_queue, CreateTask(func, arg)); // 将任务推入队列
    pthread_cond_broadcast(&p->queue_not_empty);  // 唤醒等待队列非空的线程
    pthread_mutex_unlock(&p->pool_mutex);         // 解锁
}

// 销毁线程池
void DestoryThreadPool(ThreadP *p)
{
    if (p == NULL)
    {
        return;
    }
    p->shutdown = true; // 设置线程池关闭标志

    JoinThread(p->admin_thread); // 等待管理线程结束
    free(p->admin_thread);       // 释放管理线程资源

    int len = GetListLen(&p->threads); // 获取线程列表长度
    for (int i = 0; i < len; i++)      // 唤醒所有等待线程
    {
        pthread_cond_broadcast(&p->queue_not_empty);
    }

    LNode *travelPoint = p->threads.head; // 遍历线程列表
    while (travelPoint != NULL)           // 等待所有线程结束并释放资源
    {
        Thread *t = (Thread *)travelPoint->data;
        JoinThread(t);
        free(t);
        travelPoint = travelPoint->next;
    }
    FreeDLlist(&p->threads); // 释放线程列表资源

    while (IsQEmpty(&p->task_queue) != true) // 清空任务队列
    {
        task *t = (task *)(LQPop(&p->task_queue));
        free(t);
    }
    FreeQueue(&p->task_queue); // 释放任务队列资源

    pthread_mutex_destroy(&p->pool_mutex);      // 销毁线程池互斥锁
    pthread_mutex_destroy(&p->busy_thrd_mutex); // 销毁忙碌线程互斥锁

    pthread_cond_destroy(&p->queue_not_empty); // 销毁队列非空条件变量
    pthread_cond_destroy(&p->queue_not_full);  // 销毁队列非满条件变量
}

/*************************StdSqlite.h***************************/
#ifndef _STDSQLITE_H_
#define _STDSQLITE_H_

struct StdSqlite;
typedef struct StdSqlite SQL;

SQL *InitSqlite(const char *filename);

void CreateTable(SQL *s, const char *tableName, char **prolist, int row);

void DeleteTable(SQL *s, const char *tableName);

void InsertData(SQL *s, const char *tableName, char **values, int size);

void DeleteData(SQL *s, const char *tableName, const char *where);

void UpdateData(SQL *s, const char *tableName, const char *Setvalue, const char *where);

void GetTableInfo(SQL *s, const char *tableName, char ***result, int *row, int *column);

void SelectInfo(SQL *s, const char *sql, char ***result, int *row, int *column);

void FreeInfoResult(char **result);

int GetTableLen(SQL *s, const char *tableName);

int IsTableEmpty(SQL *s, const char *tableName);

void FreeSqlite(SQL *s);

#endif

/*************************StdSqlite.c***************************/
#include <sqlite3.h>   // 包含SQLite数据库的头文件
#include <stdio.h>     // 包含标准输入输出函数的头文件
#include <stdlib.h>    // 包含通用工具函数的头文件
#include <string.h>    // 包含字符串处理函数的头文件
#include "StdSqlite.h" // 包含自定义的头文件 "StdSqlite.h"

#define true 1
#define false 0

struct StdSqlite
{
    sqlite3 *db; // SQLite数据库连接句柄
};

// 初始化SQLite数据库，打开指定文件的数据库连接
SQL *InitSqlite(const char *filename)
{
    SQL *s = (SQL *)malloc(sizeof(SQL)); // 分配内存来存储SQL结构体
    if (s == NULL)
    {
        printf("fail to InitSqlite\n"); // 内存分配失败的错误处理
        return NULL;
    }
    if (sqlite3_open(filename, &s->db) != SQLITE_OK) // 打开数据库文件，将连接句柄保存到s->db
    {
        printf("open %s error:%s\n", filename, sqlite3_errmsg(s->db)); // 打开数据库失败的错误处理
        free(s);                                                       // 释放之前分配的内存
        return NULL;
    }

    return s; // 返回初始化后的SQL结构体指针
}

// 创建数据库表格
void CreateTable(SQL *s, const char *tableName, char **prolist, int row)
{
    char property[1024] = {0}; // 用于存储表格属性的字符串
    for (int i = 0; i < row; i++)
    {
        strcat(property, prolist[i * 2]); // 将属性名添加到property字符串
        strcat(property, " ");
        strcat(property, prolist[i * 2 + 1]); // 将属性类型添加到property字符串

        if (i != row - 1)
        {
            strcat(property, ","); // 如果不是最后一个属性，添加逗号分隔符
        }
    }
    char sql[4096] = {0};                                      // 用于存储SQL语句的字符串
    sprintf(sql, "create table %s(%s);", tableName, property); // 格式化创建表格的SQL语句
    // printf("sql:%s\n", sql);                                   // 打印生成的SQL语句
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("create table error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 删除数据库表格
void DeleteTable(SQL *s, const char *tableName)
{
    char sql[4096] = {0};
    sprintf(sql, "drop table %s;", tableName);

    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("DeleteTable error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 插入数据到表格
void InsertData(SQL *s, const char *tableName, char **values, int size)
{
    char valueList[1024] = {0};
    for (int i = 0; i < size; i++)
    {
        strcat(valueList, values[i]);
        if (i != size - 1)
        {
            strcat(valueList, ",");
        }
    }

    char sql[4096] = {0};                                             // 用于存储SQL语句的字符串
    sprintf(sql, "insert into %s values(%s);", tableName, valueList); // 格式化插入数据的SQL语句
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("insert data error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 删除数据
void DeleteData(SQL *s, const char *tableName, const char *where)
{
    char sql[4096] = {0}; // 用于存储SQL语句的字符串
    if (where == NULL)
    {
        sprintf(sql, "delete from %s;", tableName); // 格式化删除数据的SQL语句
    }
    else
    {
        sprintf(sql, "delete from %s where %s;", tableName, where); // 格式化带条件删除数据的SQL语句
    }
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("delete data error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 更新数据
void UpdateData(SQL *s, const char *tableName, const char *Setvalue, const char *where)
{
    char sql[4096] = {0};                                                    // 用于存储SQL语句的字符串
    sprintf(sql, "update  %s set %s where %s;", tableName, Setvalue, where); // 格式化更新数据的SQL语句
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("updateData error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 获取表格信息
void GetTableInfo(SQL *s, const char *tableName, char ***result, int *row, int *column)
{
    char sql[4096] = {0}; // 用于存储SQL语句的字符串
    sprintf(sql, "select *from %s;", tableName);

    if (sqlite3_get_table(s->db, sql, result, row, column, NULL) != SQLITE_OK)
    {
        printf("GetTableInfo error:%s", sqlite3_errmsg(s->db));
    }
}

// 执行查询操作
void SelectInfo(SQL *s, const char *sql, char ***result, int *row, int *column)
{
    if (sqlite3_get_table(s->db, sql, result, row, column, NULL) != SQLITE_OK)
    {
        printf("GetTabelLen error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 释放查询结果
void FreeInfoResult(char **result)
{
    sqlite3_free_table(result);
}

// 获取表格长度
int GetTableLen(SQL *s, const char *tableName)
{
    char sql[4096] = {0};
    sprintf(sql, "select count(*) from %s;", tableName);

    char **result;
    int row, column;
    if (sqlite3_get_table(s->db, sql, &result, &row, &column, NULL) != SQLITE_OK)
    {
        printf("GetTabelLen error:%s\n", sqlite3_errmsg(s->db));
    }

    int len = atoi(result[column]);
    sqlite3_free_table(result);

    return len;
}

// 判断表格是否为空
int IsTableEmpty(SQL *s, const char *tableName)
{
    if (GetTableLen(s, tableName) > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// 释放SQLite数据库资源
void FreeSqlite(SQL *s)
{
    if (s == NULL)
    {
        return; // 如果传入的SQL结构体为空，直接返回
    }
    sqlite3_close(s->db); // 关闭数据库连接
    free(s);              // 释放存储SQL结构体的内存
}
