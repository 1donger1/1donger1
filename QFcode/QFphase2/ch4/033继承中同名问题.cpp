#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base
{
public:
    Base(int a)
    {
        this->a = a;
    }
    void foo()
    {
        cout << "父类的foo函数" << endl;
    }
    int a;
};

class Son : public Base
{
public:
    Son(int a1, int a2) : Base(a1), a(a2)
    {
    }

    void foo()
    {
        cout << "子类的foo函数" << endl;
    }

    int a;
};

void test01()
{
    Son p(10, 20);
    //如果子类和父类有同名的成员变量，父类的成员变量会被隐藏，访问的是子类的成员变量
    cout << p.a << endl; //20
    // 如果子类和父类有同名的成员函数，父类的成员函数会被隐藏，访问的是子类的成员函数
    p.foo();
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}
