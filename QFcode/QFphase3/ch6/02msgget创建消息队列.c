#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
 int msgget(key_t key, int msgflg);
 功能：创建一个消息队列，得到消息队列的id
 参数：
 key：键值，唯一的键值确定唯一的消息队列
 方法1：任意指定一个数
 方法2：使用ftok函数获取键值
 msgflg：消息队列的访问权限，
 一般设置为 IPC_CREAT | IPC_EXCL | 0777 或者 IPC_CREAT | 0777
 返回值：
 成功：消息队列的id
 失败：‐1
*/

int main(int argc, char *argv[])
{
    key_t mykey;
    if((mykey = ftok(".", 100)) == -1)
    {
        perror("fail to ftok");
        exit(1);
    }

    printf("mykey = %#x\n", mykey);

    //通过msgget函数创建一个消息队列
    int msqid;
    if((msqid = msgget(mykey, IPC_CREAT | 0666)) == -1)
    {
        perror("fail to msgget");
        exit(1);
    }

    printf("msqid = %d\n", msqid);

    system("ipcs -q");

    return 0;
}