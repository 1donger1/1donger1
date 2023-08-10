#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T1, class T2>
class Person;

// 类模板作为函数形参，函数需要写成函数模板
template <class T1, class T2>
void showPerson(Person<T1, T2> &p)
{
    cout << p.a << " " << p.b << endl;
}

template <class T1, class T2>
class Person
{
    //加上<>表明将函数模板声明为友元
    friend void showPerson<>(Person<T1, T2> &p);

public:
    Person(T1 a, T2 b)
    {
        this->a = a;
        this->b = b;
    }

private:
    T1 a;
    T2 b;
};

template <class T1, class T2>
void showPerson(Person<T1, T2> &p)
{
    cout << p.a << " " << p.b << endl;
}

void test01()
{
    Person<int, string> p(24, "donger");
    showPerson(p);
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}
