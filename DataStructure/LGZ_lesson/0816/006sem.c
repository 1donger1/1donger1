#include "002SystemHead.h"

void PV(int semID, int op) // 传进来的op是+1或-1
{
    struct sembuf buf;
    buf.sem_num = 0;        // 下标
    buf.sem_flg = SEM_UNDO; // 权限
    buf.sem_op = op;        // 操作-1为p，+1为v
    semop(semID, &buf, 1);
}

int main(int argc, char *argv[])
{
    key_t key = ftok("./", 20);
    int semID = semget(key, 1, IPC_CREAT | 0664);

    if (semID < 0)
    {
        perror("fail to semget");
        exit(1);
    }

#if 0
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if (pid == 0)
    {
        int num = 0;
        while (1)
        {
            semctl(semID, 0, SETVAL, 1); // 0是第一个信号量的下标,设置初始信号量为1

            // p
            PV(semID, -1);
            num++;
            sleep(1);

            if (num == 10)
            {
                PV(semID, 1);
                num = 0;
            }
            printf("child process: %d\n", num);
        }
    }
    else
    {
        while (1)
        {
            PV(semID, 1);
            printf("child is 10!\n");
            PV(semID, 1);
        }
    }

    semctl(semID, 0, IPC_RMID); // 把第0个做删除操作
#endif
    semctl(semID, 0, SETVAL, 1); // 0是第一个信号量的下标,设置初始信号量为1
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if (pid == 0)
    {
        while (1)
        {
            // PV(semID, -1);
            printf("Im child process!\n");
            sleep(3);
            printf("child awake!\n");
        }
    }

    else
    {
        while (1)
        {
            PV(semID, -1);

            printf("Im parent process!\n");
            sleep(2);
            printf("parent awake!\n");
            PV(semID, 1);
        }
    }

    semctl(semID, 0, SETVAL, 1); 

    return 0;
}