#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base
{
public:
    int a;

protected:
    int b;

private:
    int c;
};

// 公有继承方式：基类中是什么控制权限，继承到子类中也是什么控制权限
class A : public Base
{
public:
    int d;
    void show()
    {
        // 子类的成员函数去访问父类的成员：子类不可访问父类的私有成员
        //  cout << a << b << c << endl;//c是私有的
    }
};

class B : protected Base
{
    // 保护继承：将父类的公有的变成保护的，其他不变
public:
    int d;

    void show()
    {
        // cout << a << b << c <<d<<endl;//子类访问父类，不能访问父类的私有成员
    }
};

class C : private Base
{
    // 私有继承会将所有权限变成私有的
public:
    int d;
    void show()
    { // 子类访问父类，不能访问父类的私有成员，只有c不能访问，看的是继承之前的权限
        // cout << a << b << c << d << endl;
    }
};

void test01()
{
    A p;
    p.a = 10;
    p.d = 20;

    B p1;
    p1.d = 200;

    C p2;
    p2.d = 100;
}
int main(int argc, char **argv)
{

    return 0;
}