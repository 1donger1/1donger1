#ifndef __SYSTEMHEAD_H_
#define __SYSTEMHEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//Process
#include <sys/types.h>
#include <unistd.h>

//FIFO
#include <sys/stat.h>
#include <fcntl.h>

//MessageQueue
#include <sys/ipc.h>
#include <sys/msg.h>

//signal
#include <signal.h>

//shm
#include <sys/shm.h>

//sem
#include <sys/sem.h>

#endif