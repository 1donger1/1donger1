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

    Person operator+(Person &p2)
    {
        Person p(this->age + p2.age);
        return p;
    }
    int age;
};
#if 0
Person operator + (Person &p1, Person &p2)
{
    Person p(p1.age + p2.age);
    return p;
}

void test01()
{
    Person p1(10);
    Person p2(20);
    Person p3 = p1 + p2;
    cout << p3.age << endl;
}
#endif
void test02()
{
    Person p1(10);
    Person p2(20);
    Person p3 = p1 + p2;
    cout << p3.age << endl;
}

int main(int argc, char **argv)
{
    test02();

    return 0;
}