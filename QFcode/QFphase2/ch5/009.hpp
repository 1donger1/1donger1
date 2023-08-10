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

template <class T1, class T2>
Person<T1, T2>::Person(T1 a, T2 b)
{
    this->a = a;
    this->b = b;
}

template <class T1, class T2>
void Person<T1, T2>::show()
{
    cout << a << " " << b << endl;
}