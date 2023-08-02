#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define N 128

typedef struct
{
    long msg_type;    // 消息类型，必须在结构体的第一个位置并且类型必须是long
    char msg_text[N]; // 消息正文，也可以有多个成员并且类型也可以是任意
} MSG;

#define MSGTEXT_SIZE (sizeof(MSG) - sizeof(long))
/*
 ssize_t msgrcv(int msqid, void *msgp, size_t msgsz,long msgtyp, int msgflg);
 功能：从消息队列中接收数据（读操作），接收的数据会从消息队列中删除
 参数：
     msqid：消息队列id
     msgp：保存接收到的数据的结构体
     struct struct_name{
        long mtype; //消息的编号，必须大于0
        char mtext[128]; //消息正文，可以定义多个成员
    }
 msgsz：消息正文的大小
 msgtyp：设置要接收哪个消息
    0 按照写入消息队列的顺序依次读取
    >0 只读取消息队列中消息编号为当前参数的第一个消息
    <0 只读取消息队列中小于等于当前参数的绝对中内最小的第一个消息
 msgflg：标志位
     0 阻塞
    IPC_NOWAIT 非阻塞
 返回值：
    成功：接收到的消息正文的长度
    失败：‐1
*/

int main(int argc, char const *argv[])
{
    // 使用ftok函数获取键值
    key_t key;
    if ((key = ftok(".", 10)) == -1)
    {
        perror("fail to ftok");
        exit(1);
    }

    // 使用msgget函数创建一个消息队列
    int msgid;
    if ((msgid = msgget(key, IPC_CREAT | 0777)) == -1)
    {
        perror("fail to msgget");
        exit(1);
    }

    system("ipcs -q");

    //通过msgrcv函数接受消息队列中的消息(读操作)
    //注意：如果没有第四个参数指定的消息时，msgrc函数会阻塞等待
    MSG msg;

    // 如果第四个参数为0，则按照先进先出的方式读取数据
    // if(msgrcv(msgid, &msg, MSGTEXT_SIZE, 0, 0) == -1)
    // 如果第四个参数为>0，则获取当前值得消息类型的数据
    // if(msgrcv(msgid, &msg, MSGTEXT_SIZE, 2, 0) == -1)
    // 如果第四个参数为<0，则获取当前值得绝对值内消息类型最小的数据
    if (msgrcv(msgid, &msg, MSGTEXT_SIZE, -3, 0) == -1)
    {
        perror("fail to msgrcv");
        exit(1);
    }

    printf("recv_msg = %s\n", msg.msg_text);

    system("ipcs -q");

    return 0;
}