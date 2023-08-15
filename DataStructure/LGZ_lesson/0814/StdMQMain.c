#include "StdMessageQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct
// {
//     long type;
//     char content[100];
// }MSGToSend;

struct Recv_Send_MSG
{
    long type;
    char content[100];
} RSMSG;

int main()
{
    MsgQueue *msg = InitMsgQueue("./", 10);
    if (msg == NULL)
    {
        printf("InitMsgQueue fail!\n");
        return -1;
    }

    RSMSG.type = 1;
    strcpy(RSMSG.content, "Hello Donger!");

    MessageSend(msg, &RSMSG, sizeof(RSMSG));

    ClearMsgQueue(msg);

    return 0;
}
