#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(int *a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void test01()
{
    int a = 10;
    int b = 20;
    swap(&a, &b);
    cout << a << " " << b << endl;
}

void swap_ref(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void test01_ref()
{
    int a = 10;
    int b = 20;
    swap_ref(a, b);
    cout << a << " " << b << endl;
}
void get_mem(int **q)
{
    *q = (int *)malloc(5 * sizeof(int));
}

void get_mem_ref(int *&q)
{
    q = (int *)malloc(5 * sizeof(int));
}
void test03()
{
    int *p = NULL;
    get_mem(&p);
    get_mem_ref(p);
}

int & test04()
{
    static int b = 100;
    int a = 10;
    return b;//可以返回静态的变量的引用
}

int main(int argc, char **argv)
{
    // test01();
    // test01_ref();

    // test03();
    test04() = 1000;
    
    return 0;
}