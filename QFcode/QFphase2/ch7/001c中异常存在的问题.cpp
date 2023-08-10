#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mydive(int a, int b)
{
    if (b == 0)
    {
        return -1;
    }
    return a / b;
}

void test01()
{
    int ret = mydive(2, 0);

    // 结果为-1，但是C语言中这样判断，它认为返回的值-1是有问题的，虽然实际上没问题
    //  int ret = mydive(1, -1);

    if (ret == -1)
    {
        cout << "除数为0" << endl;
    }
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}