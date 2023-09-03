#ifndef __STDTHREAD_H_
#define __STDTHREAD_H_

struct StdThread;
typedef struct StdThread Thread;

Thread* InitThread(void *(*func)(void *), void *arg);

unsigned long int GetThreadId(Thread *t);

void *JoinThread(Thread *t);

void DetachTherad(Thread *t);

void CancelThread(Thread *t);

void ClearThread(Thread *t);

#endif