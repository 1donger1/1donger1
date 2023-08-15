#include "StdMessageQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    MessageRCV(msg, &RSMSG, sizeof(RSMSG), 1); // Match the message type

    printf("Received message: %s\n", RSMSG.content);

    ClearMsgQueue(msg);

    return 0;
}
