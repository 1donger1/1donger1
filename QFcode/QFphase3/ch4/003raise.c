#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/*
int raise(int sig);
功能：给调用进程本身发送信号
参数：
sig：指定的信号
返回值：
成功：0
失败：非0
raise(sig) <==> kill(getpid(), sig)

*/

int main(int argc, char *argv[])
{
    int num = 0;
    while(1)
    {
        printf("hello world\n");
        sleep(1);

        num++;

        if(num == 5)
        {
            //使用raise给当前进程本身发送信号
            raise(SIGALRM);
        }
    }

    return 0;
}