#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace nameA
{
    int a = 10;
    void foo()
    {
        cout << "hello" << endl;
    }
}

//using的声明
void test01()
{
    //当using声明的标识符和其他同名标识符有作用域的冲突时，会产生二义性
    // int a = 100;
    using nameA::a; //10
    using nameA::foo;

    cout << a << endl;

    foo();
}

void test02()
{
    int a = 1000;
    using namespace nameA;
    cout << a << endl; //1000
}

int main(int argc, char **argv)
{
    test01();
    // test02();

    return 0;
}