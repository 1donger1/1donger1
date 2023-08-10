#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <class T1, class T2>
class Animal
{
public:
    Animal(T1 a, T2 b)
    {
        age = a;
        data = b;
    }
    // int age;
    // int id;
    T1 age;
    T2 data;
};

// class Animal_1
// {
//     public:
//         int age;
//         string name;
// };

// 类模板做函数参数
void show(Animal<int, int> & p)
{
    cout << p.age << " " << p.data << endl;
}

// 上面的show()可以正常输出dog，但是如果传cat就不可以了，因为类型不匹配
// 解决方案:将函数写成函数模板(法1)
template <class T1, class T2>
void show1(Animal<T1, T2> &p)
{
    cout << p.age << " " << p.data << endl;
}

//(法2)
template <class T>
void show2(T &p)
{
    cout << p.age << " " << p.data << endl;
}

void test01()
{
    // Animal dog(10, 10);//类模板不能做自动类型推导
    Animal<int, int> dog(10, 10);//显示指定
    Animal<int, string> cat(5, "Tom");
    show1(dog);
    show1(cat);
    show2(cat);
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}