#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Longlongerror : public exception
{
public:
    Longlongerror(string data)
    {
        this->data = data;
    }

    Longlongerror(char *data)
    {
        this->data = data;
    }
    const char *what() const
    {
        return data.c_str;
    }
    string data;
};

void fun()
{
    throw Longlongerror("长长的错误");
}

void test01()
{
    try
    {
        fun();
    }
    catch (exception &p)
    {
        cout << p.what() << endl;
    }
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}