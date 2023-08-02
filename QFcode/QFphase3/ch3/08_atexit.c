#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

//atexit函数：注册进程正常结束前调用的函数，进程退出执行注册函数

void clear_fun1(void)
{
    printf("clear_fun1\n");
}

void clear_fun2(void)
{
    printf("clear_fun2\n");
}

void clear_fun3(void)
{
    printf("clear_fun3\n");
}

int main(int argc, char *argv[])
{
    //atexit函数在进程结束时才会去执行参数对应的回调函数
    //atexit多次调用后，执行顺序与调用顺序相反
    atexit(clear_fun1);
    atexit(clear_fun2);
    atexit(clear_fun3);

    printf("process exit 3 sec later!\n");

    sleep(3);

    return 0;
}