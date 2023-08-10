#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test01()
{
    // static_cast用来转换内置的数据类型，和C语言的强制类型转换一样
    int a = 1;
    char b = 2;
    double c = 3.14;
    a = static_cast<int>(b);
    a = static_cast<int>(c);
    c = static_cast<double>(a);
}

class A
{
public:
    int a;
};
class B : public A
{
public:
    int b;
};

void test02()
{
    A *p1 = new A;
    B *p2 = new B;
    // static_cast不能转换没有发生继承关系的类
    //  p1 = static_cast<A*>(p2) ;//此时没写B继承A

    // 如果两个类之间发生了继承关系，可以类型转换
    p1 = static_cast<A *>(p2); // 子转父 向上转换 是安全的
    // p2 = static_cast<A *>(p1);//父转子 向下转换 是不安全的
}

void test03()
{
    int *p1 = NULL;
    char *p2 = NULL;
    // static_cast不能用来转指针
    //  p1 = static_cast<int *>(p2);
}

/****************************dynamic_cast动态转换*********************************/
// dynamic_cast
void test04()
{
    // 动态转换不能转内置的基本数据
    int a = 1;
    char b = 2;
    // a = dynamic_cast<int>(b);//转不了
}

void test05()
{
    A *p1 = new A;
    B *p2 = new B;

    // dynamic不能用于没有发生继承关系之间的类型转换
    // dynamic可以用于发生继承关系之间的类型转换
    p1 = dynamic_cast<A *>(p2); // 子转父，安全
    // p2 = dynamic_cast<A *>(p1);//父转子，不安全
}

/****************************const_cast常量转换*********************************/
void test06()
{
    int *p1 = NULL;
    const int *p2 = NULL;
    // int *p1 = static_cast<int *>(p2);
    p1 = const_cast<int *>(p2);
    p2 = const_cast<const int *>(p1);
}

/****************************reinterpret_cast重新解释转换*********************************/
void test07()
{
    int *p1 = NULL;
    char *p2 = NULL;
    p1 = reinterpret_cast<int *>(p2);
    p2 = reinterpret_cast<char *>(p1);

    int c = 0;
    c = reinterpret_cast<int>(p2);
}

int main(int argc, char **argv)
{

    return 0;
}