#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test01()
{
    int a = 10;
    int &b = a; // 编译器优化 int * const b = &a;

    b = 0x100;//指针常量 不能改变指针变量的指向

    b = 1000; // *b = 1000;
}

void fun(int *&q) // int *&q = p --> 编译器优化 int * const q = &p;
{
}

int main(int argc, char **argv)
{
    
    
    return 0;
}