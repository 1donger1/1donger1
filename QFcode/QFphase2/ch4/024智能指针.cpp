#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    Person(int age)
    {
        this->age = age;
    }
    int age;
};

class Smartpointer
{
public:
    Smartpointer(Person *p1)
    {
        this->p = p1;
    }
    ~Smartpointer()
    {
        delete p;
        cout << "释放了" << endl;
    }
    Person *operator->()
    {
        return p;
    }

    Person operator*()
    {
        return *p;
    }
    Person *p;
};

void test01()
{
    // Person *p = new Person(10);
    Smartpointer sp(new Person(10));
    // cout << p->age << endl;
    cout << sp->age << endl;
    cout << (*sp).age << endl;


}

int main(int argc, char **argv)
{
    test01();
    return 0;
}