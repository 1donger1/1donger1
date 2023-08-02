#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void handler(int sig)
{
    printf("SIGINT\n");
}

int main(int argc, char *argv[])
{
    signal(SIGINT, handler);

#if 0
    //slepp函数是一个可重入函数，但是当执行信号处理函之后，不会回到原本的位置继续睡眠
    //sleep(10);

    //alarm函数是一个可重入函数，当他执行时，如果有信号产生并执行信号处理函数，执行完毕后，会继续运行
    alarm(10);

    while(1)
    {
        printf("hello world\n");
        sleep(1);
    }
#endif

#if 1
    char buf[32] = "";

    if(read(0, buf, 20) == -1)
    {
        perror("fail to read\n");
        exit(1);
    }

    printf("buf = [%s]\n", buf);
#endif

    return 0;
}