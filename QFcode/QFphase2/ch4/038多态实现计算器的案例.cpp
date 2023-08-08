#include <iostream>
#include <string>
#include <vector>

using namespace std;

//开发时，对源码的修改是关闭的，对扩展是开放的
class Mycalc
{
public:
    int calc(int a, int b, string cmd)
    {
        if (cmd == "+")
        {
            return a + b;
        }
        else if (cmd == "-")
        {
            return a - b;
        }
        else
        {
            return a * b;
        }
    }
};

void test01()
{
    Mycalc p;
    cout << p.calc(3, 4, "+") << endl;
    cout << p.calc(3, 4, "*") << endl;
}
/******************************************************************/
//多态实现计算器案例
class Calc
{
public:
    virtual int mycalc(int a, int b)
    {
        return 0;
    }
};

class Add : public Calc
{
public:
    int mycalc(int a, int b)
    {
        return a + b;
    }
};

class Sub : public Calc
{
public:
    int mycalc(int a, int b)
    {
        return a - b;
    }
};

class Mul : public Calc
{
public:
    int mycalc(int a, int b)
    {
        return a * b;
    }
};

int do_calc(int a, int b, Calc &obj)
{
    return obj.mycalc(a, b);
}

void test02()
{
    Add p;
    cout << do_calc(2, 3, p) << endl;
    Mul p1;
    cout << do_calc(9, 3, p) << endl;
    Sub p2;
    cout << do_calc(2, 6, p) << endl;
}

int main(int argc, char **argv)
{
    // test01();
    test02();
    return 0;
}