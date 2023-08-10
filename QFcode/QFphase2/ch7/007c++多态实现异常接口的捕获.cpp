#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Myexception
{
public:
    virtual void error() = 0;
};

class Out_of_range : public Myexception
{
public:
    void error()
    {
        cout << "Out of range" << endl;
    }
};

class Bad_cast : public Myexception
{
public:
    void error()
    {
        cout << "Bad_cast" << endl;
    }
};

void fun()
{
    // throw Out_of_range();
    throw Bad_cast();
}

void test01()
{
    try
    {
        fun();
    }
    catch (Myexception &p)
    {
        p.error();
    }
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}