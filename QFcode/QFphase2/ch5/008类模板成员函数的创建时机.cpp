#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

using namespace std;

class A
{
public:
    void showA()
    {
        cout << "showA" << endl;
    }
};

class B
{
public:
    void showB()
    {
        cout << "showB" << endl;
    }
};

template <class T>
class C
{
public:
    /*  //test01
        // 两个函数能够同时存在，编译通过
        void foo1()
        {
            obj.showA();
        }
        void foo2()
        {
            obj.showB();
        }
    */

    // 光声明的时候，也没有报错，但是在test02中调用时，编译报错
    // 说明:类模板的成员函数的创建时机是在调用时，没有调用,编译器不会创建这个函数,只有函数的声明
    void foo1();
    void foo2();
    T obj;
};

void test01()
{
    C<A> p;
    p.foo1();
    // p.foo2();//err
}

void test02()
{
    C<A> p;
    p.foo1();
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}