#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base
{
public:
    Base(int age, string name)
    {
        this->age = age;
        this->name = name;
        cout << "Base的构造" << endl;
    }
    ~Base()
    {
        cout << "Base的析构函数" << endl;
    }
    int age;
    string name;
};

// 创建子类对象的时候，必须先构建父类，需要调用父类的构造函数
class Son : public Base
{
public:
    Son(int id, int age, string name) : Base(age, name)
    {
        this->id = id;
        cout << "Son的构造函数" << endl;
    }
    ~Son()
    {
        cout << "Son的析构函数" << endl;
    }
    int id;
};

void test01()
{
    Son p(10, 18, "donger");
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}