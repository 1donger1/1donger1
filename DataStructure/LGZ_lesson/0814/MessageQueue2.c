#include "SystemHead.h"

struct Message
{
    long type; // message type
    char content[100];
};
typedef struct Message MSG;

int main(int argc, char *argv[])
{
    key_t key = ftok("./", 10);
    if (key < 0)
    {
        perror("ftok:");
        return -1;
    }

    int msgid = msgget(key, IPC_CREAT | 0777);
    if (msgid < 0)
    {
        perror("msgget:");
        return -1;
    }

    MSG msg;
    msgrcv(msgid, &msg, sizeof(MSG), 1, 0);
    printf("read from 1:%s\n", msg.content);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}