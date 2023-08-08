#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    int age;
    int yanzhi;
    // static Person *single;
    static Person * interface()
    {
        return single;
    }

private:
    static Person *single;
    Person() {} // 无参构造私有化，那么一个对象都实例不出
    Person(const Person &p) {}//拷贝构造私有化
};

Person *Person::single = new Person;

// void test01()
// {
//     Person::single->age = 20;
//     Person::single->yanzhi = 100;

//     // Person p1(*Person::single); // 调用拷贝构造实例化出一个对象
// }

void test02()
{
    Person *p = Person::interface();
    p->age = 10;
    p->yanzhi = 100;

    Person *p1 = Person::interface();
    cout << p1->age << " " << p1->yanzhi << endl;
}

int main(int argc, char **argv)
{
    test02();
    return 0;
}
