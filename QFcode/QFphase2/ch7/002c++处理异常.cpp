#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mydive(int a, int b)
{
    // 处理异常
    if (b == 0)
    {
        // 抛出异常，抛出一个类型
        // throw 1; //1是整型，即抛出int
        throw 'a'; // 抛出char
    }
    return a / b;
}

#if 0
void test01()
{
    //尝试捕获异常
    try
    {
        mydive(2, 0);
    }
    // catch(int)
    // {
    //     cout << "捕获了一个int类型的异常" << endl;
    // }
    catch (char)//如果没有捕获到抛出的异常，程序会被终止
    {
        cout << "捕获了一个char类型的异常" << endl;
    }
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}
#endif

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
        //捕获到异常，未处理，继续抛给上层调用main
        throw 'a';
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