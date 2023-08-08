#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Myint
{
    public:
    Myint(int num)
    {
        this->num = num;
    }
    Myint& operator++()
    {
        this->num = this->num + 1;
        return *this;
    }

    Myint operator++(int)
    {
        Myint temp = *this;
        this->num = this->num + 1;

        return temp;
    }
    int num;
};

ostream &operator<<(ostream &cout, Myint &p) 
{
    cout << p.num;
    return cout;
}



void test01()
{
    Myint p1(10);
    cout << p1 << endl;
    ++p1;
    cout << p1 << endl;
    cout << ++p1 << endl;
}

int main(int argc, char **argv)
{

    test01();
    return 0;
}