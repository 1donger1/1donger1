#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base
{
public:
    static int getNum()
    {
        return sNum;
    }
    static int getNum(int param)
    {
        return sNum + param;
    }

public:
    static int sNum;
};

int Base::sNum = 10;

class Derived : public Base
{
public:
    static int sNum; // 基类静态成员属性将被隐藏
#if 0
//重新定义一个函数，基类中重载的函数被隐藏
    static int getNum(int param1, int param2)
    {
        return sNum + param1 + param2;
    }
#else
    // 改变基类函数的某个特征。返回值或者参数个数，将会隐藏基类重载的函数
    static void getNum(int param1, int param2)
    {
        cout << sNum + param1 + param2 << endl;
    }
#endif
};

int Derived::sNum = 20;
void test01()
{
    Derived p1;

    // 如果子类和父类有同名的静态成员变量，父类中的静态成员变量会被隐藏
    cout << p1.sNum << endl;
    // 如果子类和父类有同名的静态成员函数，父类中的静态成员函数都会被隐藏
    p1.getNum(1, 2);
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}