#include <iostream>
#include <string>
#include <vector>

using namespace std;


void swap_int(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_char(char &a, char &b)
{
    char temp;
    temp = a;
    a = b;
    b = temp;
}

void test01()
{
    int a = 1, b = 2;
    swap_int(a, b);
    cout << "a_int = " << a << "; "
         << "b_int = " << b << endl;
}

void test02()
{
    char a = 97, b = 98;
    swap_char(a, b);
    cout << "a_char = " << a << "; "
         << "b_char = " << b << endl;
}
//函数模版来实现
template <class T>//定义一个模板，模板的通用类型为T
//紧跟函数的定义
void swap_temp(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
void test03()
{
    int a = 619, b = 817;
    swap_temp(a, b);//自动类型推导
}

int main(int argc, char **argv)
{

    test01();
    test02();
    return 0;
}