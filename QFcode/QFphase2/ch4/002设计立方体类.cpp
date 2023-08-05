#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cube
{
public:
    void set_L(int l)
    {
        L = l;
    }
    void set_W(int w)
    {
        W = w;
    }
    void set_H(int h)
    {
        W = h;
    }

    int get_L()
    {
        return L;
    }
    int get_W()
    {
        return W;
    }
    int get_H()
    {
        return H;
    }

    // 求体积
    int get_cube_V()
    {
        return L * W * H;
    }
    int get_cube_S()
    {
        return 2 * W * L + 2 * W * H + 2 * H * L;
    }

    // 判断两个立方体是否相等
    bool compare_cube(Cube &c1)
    {
        return c1.get_L() == L && c1.get_W() == W && c1.get_H() == H;
    }

private:
    int L;
    int W;
    int H;
};

bool compare_cube(Cube &c1, Cube &c2)
{
    return c1.get_L() == c2.get_L() && c1.get_W() == c2.get_W() && c1.get_H() == c2.get_H();
}

void test01()
{
    Cube c1;
    c1.set_L(10);
    c1.set_H(20);
    c1.set_W(30);
    cout << c1.get_cube_S() << endl;
    cout << c1.get_cube_V() << endl;

    Cube c2;
    c2.set_L(20);
    c2.set_W(20);
    c2.set_H(30);

    if (c1.compare_cube(c2))
    {
        cout << "立方体相等" << endl;
    }
    else
    {
        cout << "立方体不相等" << endl;
    }

    if (compare_cube(c1, c2))
    {
        cout << "立方体相等" << endl;
    }
    else
    {
        cout << "立方体不相等" << endl;
    }
}

int main(int argc, char **argv)
{
    test01();

    return 0;
}