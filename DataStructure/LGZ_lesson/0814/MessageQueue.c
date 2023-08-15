#include "SystemHead.h"

struct Message
{
    long type; // message type
    char content[100];
};
typedef struct Message MSG;

int main(int argc, char *argv[])
{
    // 获取键值
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
    msg.type = 1;
    strcpy(msg.content, "hello donger");
    if (msgsnd(msgid, &msg, sizeof(MSG), 0) <= -1)
    {
        perror("msgsnd:");
        return -1;
    }

    return 0;
}