#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    Person()
    {
    }
    Person(int age, string name)
    {
        this->age = age;
        this->name = name;
    }
    bool operator==(Person &p2)
    {
        return this->age == p2.age && this->name == p2.name;
    }

    bool operator!=(Person &p2)
    {
        return this->age != p2.age && this->name != p2.name;
    }
    int age;
    string name;
};

void test01()
{
    Person p1(10, "nan");
    Person p2(20, "donger");

    if (p1 == p2)
    {
        cout << "p1==p2" << endl;
    }
    if(p1 != p2)
    {
        cout << "p1!=p2" << endl;
    }
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}