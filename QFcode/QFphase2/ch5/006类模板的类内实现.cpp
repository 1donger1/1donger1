#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T1, class T2>
class Person
{
public:
    Person(T1 a, T2 b)
    {
        this->a = a;
        this->b = b;
    }
    void show()
    {
        cout << a << " " << b << endl;
    }

    T1 a;
    T2 b;
};

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