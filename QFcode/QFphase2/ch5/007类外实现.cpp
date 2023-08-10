#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T1, class T2>
class Person
{
public:
    Person(T1 a, T2 b);
    void show();
    T1 a;
    T2 b;
};

//类模板的成员函数在类外实现 需要写成函数模板
template <class T1, class T2>
Person<T1,T2>::Person(T1 a, T2 b)
{
    void show();
    this->a = a;
    this->b = b;
}

template <class T1, class T2>
void Person<T1, T2>::show()
{
    cout << a << " " << b << endl;
}

void test01()
{
    Person<int, string> p(10, "donger");
    p.show();
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}