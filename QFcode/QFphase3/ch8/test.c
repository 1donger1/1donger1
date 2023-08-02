#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int a;
    short b;
    double c;
    char d;
} MSG1;

typedef struct
{
    char c;
    short b;
    int a;
    double d;
} MSG2;

void test1()
{
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};

    int *p = a[0];
    printf("%d\n", *p);
}

void test2()
{
    /*
    &s[0]: 这是对 s[0] 的取地址操作，即取得 s[0] 的指针地址。
(&s[0] + 1): 这里对 &s[0] 的结果进行加法操作，将得到指向下一个指针的地址。
            因为 s[0] 是一个 char* 类型的指针，所以 &s[0] 是指向 char* 类型的指针的指针（二级指针），
            对它进行加 1，相当于移动一个指针大小的距离（根据指针类型大小移动，通常是 4 或 8 字节）。
*(&s[0] + 1): 在上一步得到的地址上使用一级指针解引用操作（即 * 运算符），
            将得到指向 s[1] 的指针，因为 s[1] 是 s[0] 的下一个元素。
**(&s[0] + 1): 在上一步得到的指针 s[1] 上再进行一次指针解引用操作，将得到 s[1] 指向的第一个字符。
            由于 s[1] 指向字符串 "jiaoyu"，所以这里将得到字符 'j'。
    综上所述，**(&s[0]+1) 的结果是字符 'j'。
    */

    char *s[10];
    s[0] = "suqian";
    s[1] = "jiaoyu";

    printf("%c\n", **(&s[0] + 1));
}
#if 0
void test3()
{
    int a[4] = {2016, 2017, 2018, 2019};
    int *ptr1 = (int *)(&a + 1);
    int *ptr2 = (int *)((int)a + 1);
    printf("%x, %x", ptr1[-1], *ptr2);
}

void test4()
{
    int a = 0, b = 3;
    switch (a + b && b++ && a++ && a)
    {
    case 0:
        a++;
    case 1:
        b++;
    case 2:
        a += b;
        break;
    case 3:
        a -= b;
    default:
        a;
    }
    printf("%d %d\n", a, b);
}
#endif
void test5()
{
    printf("%ld %ld\n", sizeof(MSG1), sizeof(MSG2));
}

int main(int argc, char *argv[])
{
    // test1();

    // test2();

    // test3();

    // test4();

    test5();

    return 0;
}