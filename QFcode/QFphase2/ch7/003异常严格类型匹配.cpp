#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mydive(int a, int b)
{
    string str = "hello";
    if (b == 0)
    {
        throw str; // 抛出char
    }
    return a / b;
}

// 异常还可以一层一层的抛
void test01()
{
    // 尝试捕获异常
    try
    {
        mydive(2, 0);
    }

    catch (char)
    {
        throw 'a';
    }
    catch (int)
    {
        cout << "捕获了一个int类型的异常" << endl;
    }
    catch (double)
    {
        cout << "捕获了一个double类型的异常" << endl;
    }
    catch (...)
    {
        cout << "捕获了一个其他类型的异常" << endl;
    }
}

int main(int argc, char **argv)
{
    try
    {
        test01();
    }
    catch (char)
    {
        cout << "捕获了一个char类型的异常" << endl;
    }
    return 0;
}