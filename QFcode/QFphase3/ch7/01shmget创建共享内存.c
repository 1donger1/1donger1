#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//  int shmget(key_t key, size_t size, int shmflg);
//  功能：创建一个共享内存
//  参数：
//  key：键值，唯一的键值确定唯一的共享内存
//  size：创建的共享内存的大小
//  shmflg：共享内存的访问权限，
//  一般为 IPC_CREAT | 0777
//  返回值：
//  成功：共享内存的id
//  失败：‐1

int main(int argc, char *argv[])
{
    key_t mykey;
    if((mykey = ftok(".", 100)) == -1)
    {
        perror("fail to ftok");
        exit(1);
    }

    //通过shmget函数创建或者打开一个共享内存，返回一个共享内存的标识符
    int shmid;
    if((shmid = shmget(mykey, 500, IPC_CREAT|0666)) == -1)
    {
        perror("fail to shmget");
        exit(1);
    }

    printf("shmid = %d\n", shmid);

    system("ipcs -m");

    return 0;
}