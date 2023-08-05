#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    Person()
    {
        cout << "无参构造" << endl;
    }

    Person(int a, string n)
    {
        cout << "有参构造" << endl;
        age = a;
        name = n;
    }
    // 拷贝构造的写法：类名(const 类名 &obj){}
    // 拷贝构造的调用时机：旧对象初始化新对象
    // 如果自定义了拷贝构造，那么系统将不再提供默认的拷贝构造
    Person(const Person &p) // 拷贝构造参数是常量引用
    // explicit Person(const Person &p)//如果加上explicit则不允许使用隐式法调用拷贝构造
    {
        cout << "拷贝构造" << endl;
        // 拷贝构造做了简单的值拷贝
        age = p.age;
        name = p.name;
    }
    ~Person()
    {
        cout << "析构" << endl;
    }

    // private:
    int age;
    string name;
};

void test01()
{
    // 如果人为提供无参和有参构造，系统将不再提供默认的无参构造
    Person p1; // 调用无参构造函数时，不能使用构造法
    Person p2(24, "Donger");
    Person p3(p2); // 调用系统提供的默认拷贝构造
    cout << p3.age << " " << p3.name << endl;
}

//匿名对象
void test02()
{
    // 匿名对象没有名字，声明周期在当前行
    Person(10, "匿名对象"); // 调用了有参构造创建了一个匿名对象
    Person();               // 调用了无参构造创建了一个匿名对像
    // Person(p1);//在定义时匿名对象不能使用括号法调用拷贝构造
}

// 显示法调用拷贝构造
void test03()
{
    // p1接收了匿名对象创建的空间
    Person p1 = Person(10, "lucy"); // 匿名对象调用了有参构造(显式法)
    Person p2 = Person(p1);         // 显示法调用拷贝构造
    Person p3 = Person();           // 显示法调用无参构造
}

// 隐示法调用拷贝构造
void test04()
{
    Person p1 = {10, "lucy"}; // 隐式法调用有参构造
    Person p2 = p1;           // 隐示法调用拷贝构造
    // Person p3;           // 隐示法不能调用无参构造
}

int main(int argc, char **argv)
{
    test03();
    return 0;
}