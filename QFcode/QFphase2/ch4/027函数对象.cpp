#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Myadd
{
public:
    int add(int a, int b)
    {
        return a + b;
    }
    int operator()(int x, int y)
    {
        return x + y;
    }
};

void test01()
{
    // Myadd p;
    // cout << p.add(3, 4) << endl;
    //p()可以像函数一样调用的对象，叫函数对象
    // cout << p(5, 6) << endl;
    cout << Myadd()(5, 6) << endl;//匿名对象Myadd().operatoor()(3,4)
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}