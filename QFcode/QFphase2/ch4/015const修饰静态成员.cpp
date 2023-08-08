#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int num = 10;//const修饰的全局变量保存在常量区，不可更改

class Person
{
public:
    int a;
    // 静态成员变量不能在类内初始化，类内只能声明，定义在全局，声明的作用只是限制静态成员变量的作用
    static int b; // 静态成员变量在编译阶段就分配内存，存在静态全局区
    const static int c = 1000;//const修饰的静态成员变量是保存在常量区，在内存中只有一份
    //静态成员函数可以访问const修饰的静态成员变量
};

int Person::b = 10; // 类中成员变量的定义

void test()
{
    cout << Person::c << endl;
    Person p1;
    cout << p1.c<< endl;
}


int main(int argc, char **argv)
{
    test();
    return 0;
}