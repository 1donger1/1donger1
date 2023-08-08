#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
Person()
{
    cout << "无参构造" << endl;
}
~Person()
{
    cout << "~析构函数" << endl;
}
    int a;
    // 静态成员变量不能在类内初始化，类内只能声明，定义在全局，声明的作用只是限制静态成员变量的作用
    static int b;//静态成员变量在编译阶段就分配内存，存在静态全局区
};

int Person::b = 10;//类中成员变量的定义

void test01()
{
    Person p1;
    p1.b = 100;
    cout << p1.b << endl;
}

void test02()
{
    cout << Person::b << endl; //通过类的作用域访问类的静态成员变量
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}