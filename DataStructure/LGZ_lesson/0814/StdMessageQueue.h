#ifndef __STDMESSAGEQUEUE_H
#define __STDMESSAGEQUEUE_H

#include <stddef.h>

struct MessageQueue;
typedef struct MessageQueue MsgQueue;

MsgQueue *InitMsgQueue(const char *__pathname, int __proj_id);

void MessageSend(MsgQueue *q, void *msg, size_t size);
void MessageRCV(MsgQueue *q, void *msg, size_t size, int type);

void ClearMsgQueue(MsgQueue *q);

#endif