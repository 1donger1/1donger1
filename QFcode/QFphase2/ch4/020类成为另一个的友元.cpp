#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Building;

class GoodGay
{
public:
    GoodGay(string hall, string bedroom); // 类内声明，类外实现
    void visit();
    Building *b;
};

class Building
{
    // friend void print_Building(Building &b);
    // friend class GoodGay;//一个类成为另一个类的友元
    friend void GoodGay::visit();//类的成员函数成为另一个类的友元

public:
    Building(string hall, string bedroom)
    {
        this->hall = hall;
        this->bedroom = bedroom;
    }
    string hall;

private:
    string bedroom;
};

GoodGay::GoodGay(string hall, string bedroom)
{
    b = new Building(hall, bedroom);
}

void GoodGay::visit()
{
    cout << b->hall << " " << b->bedroom << endl;
}

void test01()
{
    GoodGay gd("气象楼", "办公室");
    gd.visit();
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}