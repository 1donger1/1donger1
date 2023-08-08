#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    Person(int age, string name)
    {
        this->age = age;
        this->name = name;
    }

    void show()
    {
        cout << age << " " << name << " " << endl;
    }

    // 加上了const，成为常函数，不能通过this指针修改this指针指向的对象的内容
    Person Person_add(Person &p2)const
    {
        Person p(this->age + p2.age, this->name + p2.name);
        return p;
    }

    int age;
    string name;
};

void test01()
{
    Person p1(10, "lucy");
    p1.show();
}

// Person Person_add(Person &p1, Person &p2)
// {
//     Person p(p1.age + p2.age, p1.name + p2.name);
//     return p;
// }
void test02()
{
    Person p1(10, "hello");
    Person p2(20, "world");

    // Person p3 = Person_add(p1, p2);
    // p3.show();

    Person p3 = p1.Person_add(p2);
    p3.show();
}

int main(int argc, char **argv)
{
    test02();
    return 0;
}