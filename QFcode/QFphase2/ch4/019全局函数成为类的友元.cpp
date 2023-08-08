#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Building
{
    friend void print_Building(Building &b);

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

void print_Building(Building &b)
{
    cout << b.hall << " " << b.bedroom << endl;
}

void test01()
{
    Building b1("气象楼", "办公室");
    print_Building(b1);
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}