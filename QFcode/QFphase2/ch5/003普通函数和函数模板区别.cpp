#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Myadd(int a, int b)
{
    cout << "普通函数" << endl;
    return a + b;
}
template <class T>
T Myadd(T a, T b)
{
    cout << "函数模板" << endl;
    return a + b;
}

void test01()
{
    int a = 10;
    char b = 20;
    Myadd(a, a);      // 先调用普通函数,省去推导步骤
    Myadd<>(a, a);    // 加<>，指定使用模板函数
    Myadd<int>(a, a); // 指定调用模板函数
    Myadd(a, b);      // 调用普通函数，因为普通函数可以自动类型转换
    // Myadd<>(a, b);    // 函数模版不会做自动类型推导
}

void test02()
{
    cout << "test02" << endl;
    char a = 'a';
    char b = '0';
    // 普通函数也可以匹配这个函数，因为普通函数可以自动类型转换
    // 但是此时函数模板能够有更好的匹配
    // 如果函数模板可以产生一个更好的匹配，那么选择函数模板
    Myadd(a, b);
}

int main(int argc, char **argv)
{
    test01();
    test02();
    return 0;
}