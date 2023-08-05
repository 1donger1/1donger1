#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    Person()
    {
        cout << "Person的无参构造" << endl;
    }

    ~Person()
    {
        cout << "Person的析构" << endl;
    }
    int a;
};

void test01()
{
    
    //此时运行，没有任何结果-->说明malloc和free动态申请和释放内存时，不会调用构造和析构
    Person *p = (Person *)malloc(sizeof(Person));
    free(p);
    
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}
