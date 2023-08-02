#include <stdio.h>
#include <stdlib.h>

/*
在 C 语言中，static 关键字用于声明静态变量。
静态变量与普通变量不同，它们的生存期和作用域是不同的。
静态变量在声明时被初始化，只被初始化一次，而且在整个程序的生命周期内都保持存在。
在函数内声明的静态变量只能在该函数内访问，而在函数外声明的静态变量则只能在该文件内访问。

*/

void test_static1()
{
    static int num = 0;
    num++;
    printf("%d ", num);
}

void test_static2()
{
    int i, num;
    num = 2;
    for (i = 0; i < 3;i++)
    {
        printf("num 变量为 %d\n", num);
        num++;
        {
            static int num = 1;
            printf("内置模块 num变量为 %d\n", num);
            num++;
        }
    }
}

int main(int argc, char *argv[])
{

    // test_static1();
    // test_static1();
    // test_static1();
    // test_static1();

    test_static2();

    printf("\n");
    return 0;
}