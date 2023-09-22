#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// vector迭代器
void test01()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    vector<int>::reverse_iterator it_start = v.rbegin();
    vector<int>::reverse_iterator it_end = v.rend();
    for (; it_start != it_end; it_start++)
    {
        cout << *it_start << " ";
    }
    cout << endl;
}

// 空间配置
void test02()
{
    vector<int> v;
    for (int i = 0; i < 50; i++)
    {
        v.push_back(i);
        cout << "capacity: " << v.capacity() << endl;
    }
}

/*vector的API*/

// 1.vector的构造函数
/*
vector<T> v; //采用模板实现类实现，默认构造函数
vector(v.begin(), v.end());//将v[begin(), end())区间中的元素拷贝给本身。
vector(n, elem);//构造函数将n个elem拷贝给本身。
vector(const vector &vec);//拷贝构造函数。
*/
void print(int a)
{
    cout << a << " ";
}
void test03()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);

    // vector<int> v2(v1);
    // vector<int> v2(v1.begin(), v1.end());
    vector<int> v2(v1.begin() + 1, v1.end());

    for_each(v2.begin(), v2.end(), print);
    cout << endl;
}

// 2.常用赋值操作
/*
2 assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
3 assign(n, elem);//将n个elem拷贝赋值给本身。
4 vector& operator=(const vector &vec);//重载等号操作符
5 swap(vec);// 将vec与本身的元素互换。
6 */
void test04()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);

    vector<int> v2;
    v2.push_back(10);
    v2.push_back(20);
    v2.push_back(30);
    v2.push_back(40);
    // v2.assign(v1.begin(), v1.end());
    // v2.assign(10, 5);
    // v2 = v1;
    for_each(v2.begin(), v2.end(), print);
    cout << endl;

    v2.swap(v1);

    for_each(v2.begin(), v2.end(), print);
    cout << endl;
}

// 3.vector大小操作
/*
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(int num);//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长>度的元素被删除。
capacity();//容器的容量
reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问。
*/
void test05()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    cout << "size:" << v1.size() << endl;
    cout << "capacity:" << v1.capacity() << endl;

    if (v1.empty())
    {
        cout << "v1 is empty" << endl;
    }
    else
    {
        cout << "v1 is not empty" << endl;
    }

    v1.resize(10);
    for_each(v1.begin(), v1.end(), print);
    cout << endl;

    vector<int> v2;
    v2.resize(100);
    cout << "v2 size:" << v2.size() << endl;
    cout << "v2 capacity:" << v2.capacity() << endl;
}

// 4.vector数据存取操作
/*
 at(int idx); //返回索引idx所指的数据，如果idx越界，抛出out_of_range异常。
 operator[];//返回索引idx所指的数据，越界时，运行直接报错
 front();//返回容器中第一个数据元素
 back();//返回容器中最后一个数据元素
 */
void test06()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    cout << "v1.at(2):" << v1.at(2) << endl;
    cout << "v1[2]:" << v1[2] << endl;

    cout << "v1 front:" << v1.front() << endl;
    cout << "v1 back:" << v1.back() << endl;
}

// 5.vector插入和删除操作
/*
insert(const_iterator pos, int count,ele);//迭代器指向位置pos插入count个元素ele.
push_back(ele); //尾部插入元素ele
pop_back();//删除最后一个元素
erase(const_iterator start, const_iterator end);//删除迭代器从start到end之间的元素
erase(const_iterator pos);//删除迭代器指向的元素
clear();//删除容器中所有元素
*/
void test07()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    v1.insert(v1.begin() + 1, 2, 10);
    for_each(v1.begin(), v1.end(), print);
    cout << endl;

    // 1 10 10 2 3 4 5
    // 删除指定元素
    v1.erase(v1.begin() + 3); // 删除2
    for_each(v1.begin(), v1.end(), print);
    cout << endl;

    // 1 10 10  3 4 5
    // 删除区间
    v1.erase(v1.begin() + 1, v1.end() - 3); // 删除俩10
    for_each(v1.begin(), v1.end(), print);
    cout << endl;

    // 输出所有元素
    v1.clear();
    for_each(v1.begin(), v1.end(), print);
    cout << endl;
}

/*
使用swap收缩空间
*/
void test08()
{

    vector<int> v1;
    for (int i = 0; i < 10000; i++)
    {
        v1.push_back(i);
    }
    cout << "v1 size:" << v1.size() << ", v1.capacity" << v1.capacity() << endl;

    v1.resize(10); // size变为10但是capacity没变
    cout << "v1 size:" << v1.size() << ", v1.capacity" << v1.capacity() << endl;

    vector<int>(v1).swap(v1); // size和capacity都变10
    cout << "v1 size:" << v1.size() << ", v1.capacity" << v1.capacity() << endl;
}

/*
计算重新分配多少次内存
*/
void test09()
{
    vector<int> v;
    int *p = NULL;
    int count = 0;
    for (int i = 0; i < 10000; i++)
    {
        v.push_back(i);
        if (p != &v[0])
        {
            count++;
            p = &v[0];
        }
    }
    cout << "count:" << count << endl;
}

/*
vector容器的排序
*/

bool compare(int v1, int v2)
{
    return v1 > v2;
}
void test10()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(2);
    v.push_back(5);
    v.push_back(1);
    v.push_back(6);
    v.push_back(3);
    v.push_back(7);
    v.push_back(4);
    v.push_back(8);
    v.push_back(9);
    for_each(v.begin(), v.end(), print);
    cout << endl;

    sort(v.begin(), v.end());          // 默认从小到大
    sort(v.begin(), v.end(), compare); // 从大到小
    for_each(v.begin(), v.end(), print);
    cout << endl;
}

class Person
{
public:
    Person(int age, string s)
    {
        this->age = age;
        this->name = s;
    }
    int age;
    string name;
};

void print_person(Person &p)
{
    cout << p.age << " " << p.name << endl;
}

bool compare_person(Person &p1, Person &p2)
{
    return p1.age > p2.age;
}
void test11()
{
    vector<Person> v;
    v.push_back(Person(10, "aaa"));
    v.push_back(Person(2, "bbb"));
    v.push_back(Person(5, "ccc"));
    v.push_back(Person(1, "ddd"));
    v.push_back(Person(6, "eee"));
    v.push_back(Person(3, "fff"));
    v.push_back(Person(7, "ggg"));

    for_each(v.begin(), v.end(), print_person);
    cout << endl;

    sort(v.begin(), v.end(), compare_person);
    for_each(v.begin(), v.end(), print_person);
    cout << endl;
}

int main(int argc, char **argv)
{
    test11();

    return 0;
}