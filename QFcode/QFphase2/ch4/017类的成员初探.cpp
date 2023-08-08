#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    int a;
    static int b; // 静态成员不存在类实例化的对象中
    void show()   // 普通成员函数不存在类实例化的对象中
    {
        cout << a << " " << b << endl;
    }
    static void show1() // 静态成员函数不存在类实例化的对象中
    {
        cout << b << endl;
    }
};
int Person::b = 11;

void test01()
{
    Person p;
    p.show();
    // 空类的大小不是0而是1
    cout << "sizeof(Person) = "<< sizeof(Person) << endl;
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}