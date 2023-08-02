#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// int msgctl(int msqid, int cmd, struct msqid_ds *buf);
//  功能：设置或者获取消息队列的信息
//  参数：
//  msqid：指定的消息队列的id
//  cmd：具体操作的指令
//  IPC_SET 设置属性
//  IPC_STAT 获取属性
//  IPC_RMID 删除消息队列
//  msqid_ds：设置或者获取消息队列的属性
//  返回值：
//  成功：0
//  失败：‐1

int main(int argc, char *argv[])
{
    key_t key;
    if ((key = ftok(".", 50)) == -1)
    {
        perror("fail to ftok");
        exit(1);
    }

    // 使用msgget()创建一个消息队列
    int msgid;
    if ((msgid = msgget(key, IPC_CREAT | 0777)) == -1)
    {
        perror("fail to msgget");
        exit(1);
    }
    printf("msgid = %d\n", msgid);
    system("ipcs -q");

    // 使用msgctl()函数删除消息队列
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("fail to msgctl");
        exit(1);
    }

    system("ipcs -q");

    return 0;
}