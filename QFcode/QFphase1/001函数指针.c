#include <stdio.h>

/*
咱们定义的函数，在运行程序的时候，会将函数的指令加载到内存的代码段，所以函数也有
起始地址。
c语言规定：函数的名字就是函数的首地址，即函数的入口地址 咱们就可以定义一个指针
变量，来存放函数的地址，这个指针变量就是函数指针变量。

 int (*p)(int,int);//定义了一个函数指针变量p,p指向的函数

*/

#include <stdio.h>
int add(int x, int y)
{
    return x + y;
}
int sub(int x, int y)
{
    return x - y;
}
int mux(int x, int y)
{
    return x * y;
}
int dive(int x, int y)
{
    return x / y;
}
int process(int (*p)(int, int), int a, int b)
{
    int ret;
    ret = (*p)(a, b);
    return ret;
}
int main(int argc, char *argv[])
{
    int num;
    num = process(add, 2, 3);
    printf("num = %d\n", num);

    num = process(sub, 2, 3);
    printf("num = %d\n", num);

    num = process(mux, 2, 3);
    printf("num = %d\n", num);

    num = process(dive, 2, 3);
    printf("num = %d\n", num);
    
    return 0;
}