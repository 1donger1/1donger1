#include "StdMessageQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


// Process
#include <sys/types.h>
#include <unistd.h>

// FIFO
#include <sys/stat.h>
#include <fcntl.h>

// MessageQueue
#include <sys/ipc.h>
#include <sys/msg.h>


struct MessageQueue
{
    key_t key;
    int msgid;
};


MsgQueue *InitMsgQueue(const char *__pathname, int __proj_id)
{
    MsgQueue *q = (MsgQueue *)malloc(sizeof(MsgQueue));
    if (q == NULL)
    {
        printf("InitMsgQueue malloc fail!\n");
        return NULL;
    }
    q->key = ftok("./", 10);
    if (q->key < 0)
    {
        perror("ftok:");
        return NULL;
    }

    q->msgid = msgget(q->key, IPC_CREAT | 0777);
    if (q->msgid < 0)
    {
        perror("msgget:");
        return NULL;
    }
    return q;
}

void MessageSend(MsgQueue *q, void *msg, size_t size)
{ 
    if(msgsnd(q->msgid, msg, size, 0) == -1)
    {
        perror("msgsnd:");
    }
}

void MessageRCV(MsgQueue *q, void *msg, size_t size, int type)
{
    if(msgrcv(q->msgid, msg, size, type, 0) == -1)
    {
        perror("msgrcv");
    }
}

void ClearMsgQueue(MsgQueue *q)
{
    msgctl(q->msgid, IPC_RMID, NULL);
    free(q);
}
