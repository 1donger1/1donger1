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
    Person(int age1, char *name1)
    {
        this->age = age1;
        name = new char[strlen(name1) + 1];
        strcpy(name, name1);
    }
    Person &operator=(Person &p1)
    {
        this->age = p1.age;
        this->name = new char[strlen(p1.name) + 1];
        strcpy(this->name, p1.name);
        return *this;
    }
    ~Person()
    {
        delete[] name;
    }
    int age;
    char *name;
};

void test01()
{
    Person p1(10, "bob");
    Person p2;
    p2 = p1;
    cout << p2.age << " " << p2.name << endl;
}

int main(int argc, char **argv)
{

    test01();
    return 0;
}