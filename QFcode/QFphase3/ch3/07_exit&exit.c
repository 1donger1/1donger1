#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

void myfun()
{
    printf("nihao beijing");

    //测试return-->
    //除了可以返回值以外，在主函数中使用可以退出进程，但是在子函数中使用只能退出当前的函数
    //return;

    //测试exit-->
    //可以退出一个进程并且可以刷新缓冲区
    // exit(0);

    // 测试_exit-->
    // 可以退出一个进程但是不可以刷新缓冲区
    // _exit(0);
}

int main(int argc, char *argv[])
{
    printf("hello world\n");

    myfun();

    printf("hello kitty\n");

    return 0;
}