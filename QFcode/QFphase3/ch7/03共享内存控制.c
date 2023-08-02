#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*
 int shmctl(int shmid, int cmd, struct shmid_ds *buf);
 功能：设置或者获取共享内存你的属性
 参数：
 shmid：共享内存的id
 cmd：执行操作的命令
 IPC_STAT 获取共享内存的属性
 IPC_SET 设置共享内存的属性
 IPC_RMID 删除共享内存
 shmid_ds：共享内存的属性结构体
 返回值：
 成功：0
 失败：‐1
*/

int main(int argc, char *argv[])
{
    key_t mykey;
    //使用ftok函数获取键值
    if((mykey = ftok(".", 100)) == -1)
    {
        perror("fail to ftok");
        exit(1);
    }

    //通过shmget函数创建或打开一个共享内存，返回一个共享内存的标识符
    int shmid;
    if((shmid = shmget(mykey, 500, IPC_CREAT|0664)) == -1)
    {
        perror("fail to ftok");
        exit(1);
    }

    printf("shmid = %d\n", shmid);

    system("ipcs -m");

    //通过shmctl函数删除共享内存
    if(shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("fail to shmctl");
        exit(1);
    }

    system("ipcs -m");

    return 0;
}