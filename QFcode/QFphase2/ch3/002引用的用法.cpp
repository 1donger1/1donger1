#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test01()
{
    int a = 10;
    int &b = a; // 引用一旦初始化，之后不能改变引用的标识
    b = 100;
    cout << a << endl;

    int c = 1;
    // b=c;//代表把c的值赋值给b，不是给c取别名b
    // int &d;//引用定义必须初始化
}

void test02()
{
    int a[5] = {1, 2, 3, 4, 5};
    // int(&arr)[5] = a;//方式一

    typedef int ARR[5];
    ARR &arr = a;
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    // test01();
    test02();

    return 0;
}