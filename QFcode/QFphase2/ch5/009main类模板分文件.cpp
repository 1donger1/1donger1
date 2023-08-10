#include <iostream>
#include <string>
#include <vector>
#include "009.hpp"

using namespace std;

int main(int argc, char **argv)
{
    //调用构造函数和show函数需要创建，但是没有这两个函数的定义，不能创建
    //解决方案，将这两个函数定义写在.h文件中
    Person<int, int> p(19, 17);
    p.show();

    return 0;
}