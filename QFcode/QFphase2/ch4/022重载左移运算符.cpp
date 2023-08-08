#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
    friend ostream &operator<<(ostream &cout, Person &p);

public:
    Person(int age)
    {
        this->age = age;
    }

private:
    int age;
};

ostream &operator<<(ostream &cout, Person &p)
{
    cout << p.age;
    return cout;
}

void test01()
{
    Person p1(10);
    cout << p1 << endl;
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}