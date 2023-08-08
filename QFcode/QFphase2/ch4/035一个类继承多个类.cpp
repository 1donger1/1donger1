#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A
{
public:
    int a;
};

class B
{
public:
    int a;
};

class C : public A, public B
{
public:
    int c;
};

void test01()
{
    C p;
    p.A::a = 10;
    p.B::a = 20;

    p.c = 30;
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}