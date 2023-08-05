#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{

public:
    int m_a, m_b, m_c;
    // 先定义的m_a, m_b, m_c，然后再分别赋值
    // Person(int a, int b, int c)
    // {
    //     m_a = a;
    //     m_b = b;
    //     m_c = c;
    // }

    // 使用初始化列表
    // 先声明了m_a, m_b, m_c,再根据声明的顺序进行定义初始化
    Person(int a, int b, int c) : m_a(a), m_b(b), m_c(c)
    {
    }

    void show()
    {
        cout << m_a << " " << m_b << " " << m_c << endl;
    }
    // ~Person();
};

void test01()
{
    Person p1(2, 3, 5);
    p1.show();
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}