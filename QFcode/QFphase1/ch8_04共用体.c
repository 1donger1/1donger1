#include <stdio.h>

/*
共用体的特点：
1、同一内存段可以用来存放几种不同类型的成员，但每一瞬时只有一种起作用
2、共用体变量中起作用的成员是最后一次存放的成员，在存入一个新的成员后原有的
成员的值会被覆盖
3、共用体变量的地址和它的各成员的地址都是同一地址

共用体的大小是其占内存长度最大的成员的大小
*/

union UN
{
    int a;
    int b;
    int c;
};

int main(int argc, char *argv[])
{
    union UN un;
    un.a = 100;
    un.c = 200;
    un.b = 300;
    printf("a = %d, b = %d, c = %d\n", un.a, un.b, un.c);
    return 0;
}