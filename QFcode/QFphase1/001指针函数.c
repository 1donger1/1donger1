#include <stdio.h>

// 指针函数本质是一个函数，只不过函数的返回值是一个指针
// 指针函数：指针作为函数的返回值
char *fun()
{
    // 栈区开辟的空间会随着当前代码段的结束而释放空间
    // char str[100]="hello world";
    // 静态区的空间不会随着当前代码段的结束而释放空间
    static char str[100] = "hello world";
    return str;
}
int main()
{
    char *p;
    p = fun();
    printf("p = %s\n", p);
}
