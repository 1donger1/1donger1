#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class Base
{
public:
    Base(T a)
    {
        this->a = a;
    }
    T a;
};

class Son1 : public Base<int> // 必须指明类型(int)
{
public:
    Son1(int x1, int a) : Base<int>(a), x(x1)
    {
    }
    int x;
};

template <class T1, class T2>
class Son2 : public Base<T2>
{
public:
    Son2(T1 x1, T2 a) : Base<T2>(a), x(x1)
    {
    }
    T1 x;
};

void test01()
{
    Son1 p(10, 20);
    Son2<int, string> p2(15, "jerry");
}

int main(int argc, char **argv)
{

    return 0;
}