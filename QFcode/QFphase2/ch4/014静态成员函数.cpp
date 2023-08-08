#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    int a;
    // 静态成员变量不能在类内初始化，类内只能声明，定义全局
    // 声明的作用只是限制静态成员变量的作用域
    static int b; // 静态成员变量，在编译阶段就分配内存，存在静态全局区
    void show()
    {
        cout << a << " " << b << endl;
    }

    static void static_show() // 静态成员函数可以访问静态成员变量，不能访问普通成员的变量
    {
        cout << " " << b << endl;
    }
};

int Person::b = 100;

void test01()
{
    Person::static_show();//通过类的作用域访问静态成员函数
    Person p1;
    p1.static_show();//通过对象访问静态成员函数
}

int main(int argc, char **argv)
{

    return 0;
}