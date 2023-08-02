#include <stdio.h>

/*
指针数组本身是个数组，是个指针数组，是若干个相同类型的指针变量构成的集合

int *p[10];//定义了一个整型的指针数组p，有10个元素p[0]~p[9],每个元素都是int*类型的变量

*/

int main(int argc, char *argv[])
{
    char *name[5] = {"chen", "chuang", "from", "jiangsu", "suqian"};

    int i;
    for (i = 0; i < 5; i++)
    {
        printf("name[%d]:%s\n", i, name[i]);
    }

    return 0;
}