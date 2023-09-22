#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void print(int val)
{
    cout << val << " ";
}

void test01()
{
    // STL中的标准容器之一:动态数组
    // 容器中每个元素是int类型
    vector<int> v;
    v.push_back(1); // 尾插
    v.push_back(2);
    v.push_back(3);

    // 若需要访问容器内的元素，需要拿到容器首元素的迭代器(指针)
    // v.end()指向最后一个元素的下一个位置
    // 迭代器类型vector<int>::iterator
    // for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    // {
    //     cout << *it << endl;
    // }

    // 加上#include<algorithm>
    // for_each(v.begin(), v.end(), [](int n) { cout << n << endl; });
    // cout << endl;
    for_each(v.begin(), v.end(), print);
    cout << endl;
}

// 定义一个Person类
class Person
{
public:
    Person(int age)
    {
        this->age = age;
    }
    int age;
};

// 迭代器指向的是自定义类型
void print_person(Person &p)
{
    cout << p.age << endl;
}
void test02()
{
    Person p1(1);
    Person p2(2);
    Person p3(3);
    Person p4(4);

    vector<Person> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    vector<Person>::iterator it_start = v.begin();
    vector<Person>::iterator it_end = v.end();
    for (; it_start != it_end; it_start++)
    {
        print_person(*it_start);
    }
}

// 迭代器指向的是一个容器
void print_vector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
void test03()
{
    vector<vector<int>> v;
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    for (int i = 0; i < 3; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 10);
        v3.push_back(i + 100);
    }

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    vector<vector<int>>::iterator it = v.begin();
    for(; it != v.end(); it++)
    {
        //*it得到的是vector<int>
        vector<int>::iterator it1 = (*it).begin();
        vector<int>::iterator it2 = (*it).end();

        for (; it1 != it2; it1++)
        {
            cout << *it1 << endl;
        }
    }
}

int main(int argc, char **argv)
{
    test03();
    return 0;
}