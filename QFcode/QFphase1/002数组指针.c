#include <stdio.h>

/*
数组指针的
概念：本身是个指针，指向一个数组，加1跳一个数组，即指向下个数组。
作用：就是可以保存二维数组的首地址

数组指针的定义方法：
指向的数组的类型（*指针变量名）[指向的数组的元素个数]
int (*p)[5];//定义了一个数组指针变量p，p指向的是整型的有5个元素的数组
p+1 往下指5个整型，跳过一个有5个整型元素的数组。
*/

void test()
{
    int a[3][5];
    int(*p)[5];

    printf("a = %p\n", a);
    printf("a+1 = %p\n", a+1);

    p = a;
    printf("p = %p\n", p);
    printf("p+1 = %p\n", p + 1);
}

int main(int argc, char *argv[])
{
    test();

    return 0;
}
