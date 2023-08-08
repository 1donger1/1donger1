#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal
{
    public:
    virtual void speak()//虚函数
    {
        cout << "动物在说话" << endl;
    }
};

class Dog:public Animal
{
    public:
    //重写虚函数 函数的返回值 参数 函数名一致
    void speak()
    {
        cout << "狗在说话" << endl;
    }
};

class Cat : public Animal
{
public:
    void speak()
    {
        cout << "猫在说话" << endl;
    }
};

//如果两个类发生了继承，父类和子类编译器会自动转换，不需要人为转换
void do_work(Animal &obj)
{
    obj.speak();//地址早绑定   ----函数前面加上virtual关键字-->>>地址晚绑定
}

void test01()
{
    Animal p1;
    do_work(p1);

    Dog p2;
    do_work(p2);

    Cat p3;
    do_work(p3);
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}