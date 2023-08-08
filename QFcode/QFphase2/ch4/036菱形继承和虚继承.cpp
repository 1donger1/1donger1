#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal
{
public:
    int age;
};

class Sheep : virtual public Animal
{
public:
    int id;
};

class Camel : virtual public Animal
{
    int camel_num;
};

class Shenshou : public Sheep, public Camel
{
public:
    int a;
};

void test01()
{
    Shenshou p;
    p.age = 10;
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}