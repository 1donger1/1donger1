#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
    while(1)
    {
        printf("hello world\n");


        //当运行到sleep()函数后，程序会在此位置等待设定的秒数，当秒数到达后，代码会接着执行
        //sleep()运行时为等待态，时间到达后会切换到就绪态，如果代码继续运行到运行态
        sleep(2);
    }

    return 0;
}