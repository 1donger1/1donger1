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

    Person(int a)
    {
        age = a;
        cout << "有参构造" << endl;
    }

    ~Person()
    {
        cout << "析构" << endl;
    }
    int age;
};

void test01()
{
    int *p = new int; // 申请一块内存 sizeof(int)大小，并且对这块空间进行初始化
    cout << *p << endl;

    *p = 100;
    cout << *p << endl;
    delete p; // 释放申请的空间
}

//申请一个对象
void test02()
{
    Person *p = new Person;//这个空间大小为sizeof(Person)
    delete p;
}

/*****************/
void test04()
{
    //new时调用有参构造
    Person * p = new Person(10);
    delete p;

    Person *p1 =  new Person[10];//注意new对象的数组时不能调用有参构造 只能调用无参构造
    delete[] p1;
}
/*****************/
//void * 问题
void test05()
{
    void *p = new Person;
    delete p;//p的类型是void* 类型，不会调用析构函数
}

//申请一个数组
void test03()
{
    //new一个数组时，返回的是该数组的首元素的地址
    int *p = new int[10];
    for (int i = 0; i < 10; i++)
    {
        p[i] = i + 100;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << p[i] << " ";
    }
    cout << endl;
    delete[] p;
}

int main(int argc, char **argv)
{

    test04();
    return 0;
}