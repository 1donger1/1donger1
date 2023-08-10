#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Myexecption
{
public:
    Myexecption()
    {
        cout << "构造" << endl;
    }
    ~Myexecption()
    {
        cout << "析构" << endl;
    }
    void error()
    {
        cout << "my error" << endl;
    }
};

void fun()
{
    // throw Myexecption();//如果抛出匿名对象，它的生命周期在catch里面
    Myexecption p1;
    throw p1;//p1生命周期在throw之后，调用两次构造
}

void test01()
{
    try
    {
        fun();
    }
    //如果没用&,就会多出一个对象，会调用两次析构
    catch(Myexecption &p)
    {
        p.error();
    }
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}