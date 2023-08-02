#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/*
2 void abort(void);
3 功能：向进程发送一个SIGABRT信号，默认情况下进程会退出。
4 参数：无
5 返回值：无
*/

//注意：即使SIGABRT信号被加入阻塞集，一旦进程调用了abort函数，进程也还是会被终止，且在终止前会刷新缓冲区，关闭文件描述符
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
            abort();
        }
    }

    return 0;
}