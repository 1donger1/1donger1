#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    // 构造函数 1.函数名和类名一致，没有返回值，不能写void
    // 可以有参数，可以发生函数重载
    Person(int age, string name)
    {
        cout << "Person的构造函数" << endl;
        m_age = age;
        m_name = name;
    }

    // 析构函数 函数名:类名前面加上~ 没有返回值 不可以有参数，不能重载
    ~Person()
    {
        cout << "析构函数" << endl;
    }

    Person()
    {
    }

private:
    int m_age;
    string m_name;
};

void test01()
{
    Person p1(24, "Donger");
    //函数结束，销毁之前，自动调用析构函数
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}