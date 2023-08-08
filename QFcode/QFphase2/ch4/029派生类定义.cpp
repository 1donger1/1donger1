#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal
{
public:
    int age;
    void print()
    {
        cout << age << endl;
    }
};

class Dog : public Animal
{
public:
    int tail_len;
};

void test()
{
    Dog dog;
    dog.age = 2;
}

int main(int argc, char **argv)
{

    return 0;
}