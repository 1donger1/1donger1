#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void array_sort(T *a, int n)
{
    int flag;
    for (int i = n - 1; i > 1; i--)
    {
        flag = 0;
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[j + 1])
            {
                T temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            return;
        }
    }
}

template <class T>
void print_array(T *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << p[i] << " ";
    }
    cout << endl;
}

void test01()
{
    int a[] = {1, 5, 7, 3, 9, 6};
    array_sort(a, sizeof(a) / sizeof(a[0]));
    print_array(a, sizeof(a) / sizeof(a[0]));
}

void test02()
{
    double b[] = {3.1, 2.5, 6.4, 9.1, 8.7};
    array_sort(b, sizeof(b) / sizeof(b[0]));
    print_array(b, sizeof(b) / sizeof(b[0]));
}

int main(int argc, char **argv)
{
    test01();
    test02();
    return 0;
}
