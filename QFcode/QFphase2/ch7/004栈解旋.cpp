#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    Person(string name)
    {
        cout << "构造" << endl;
        this->name = name;
    }
    ~Person()
    {
        cout << "析构 " << endl;
    }
        string name;
};

void fun()
{
    //在try到throw之间定义的对象，在throw之后会被释放
    Person p2("chuang");
    Person p3("chen");
    cout << "001" << endl;
    throw 1;
}

void test01()
{
    try
    {
        Person p1("donger");
        fun();
    }
    catch (int)
    {
        cout << "002" << endl;
        cout << "捕获到异常" << endl;
    }
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}