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
