#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Person
{
public:
    Person(int age, char *str)
    {
        cout << "有参构造" << endl;
        m_age = age;
        name = (char *)malloc(strlen(str) + 1);
        strcpy(name, str);
    }
    //实现深拷贝
    Person(const Person &p)
    {
        m_age = p.m_age;
        name = (char*)malloc(strlen(p.name) + 1);
        strcpy(name, p.name);
    }

    void show()
    {
        cout << name << " " << m_age << endl;
    }

    ~Person()
    {
        if(name != NULL)
        {
            free(name);
            name = NULL;
        }
        cout << "析构" << endl;
    }

    int m_age;
    char *name;
};

void test01()
{
    Person p(10, "bob");
    p.show();
    Person p1(p);//调用拷贝构造函数
    p1.show();//浅拷贝出现问题！！报错！！-->解决方法，写一个拷贝构造函数，别用默认的
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}