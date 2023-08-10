#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

void fun()
{
    //
    // throw out_of_range("越界");
    throw invalid_argument("段错误");
}

void test01()
{
    try
    {
        fun();
    }
    catch (exception &p)
    {
        cout << p.what() << endl;
    }
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}