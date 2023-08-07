#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Point
{
public:
    void setX(int x)
    {
        mX = x;
    }
    void setY(int y)
    {
        mY = y;
    }

    int GetX()
    {
        return mX;
    }
    int GetY()
    {
        return mY;
    }

private:
    int mX;
    int mY;
};

class Circle
{
public:
    void setP(int x, int y)
    {
        mp.setX(x);
        mp.setY(y);
    }
    void setR(int r)
    {
        mR = r;
    }
    Point &GetP()
    {
        return mp;
    }
    int GetR()
    {
        return mR;
    }

    void IsPointInCircle(Point &point)
    {
        int distance = (point.GetX() - mp.GetX()) * (point.GetX() - mp.GetX()) + (point.GetY() - mp.GetY()) * (point.GetY() - mp.GetY());
        int radius = mR * mR;
        if (distance < radius)
        {
            cout << "Point(" << point.GetX() << "," << point.GetY() << ")在圆内" << endl;
        }
        else if (distance > radius)
        {
            cout << "Point(" << point.GetX() << "," << point.GetY() << ")在圆外" << endl;
        }
        else
        {
            cout << "Point(" << point.GetX() << "," << point.GetY() << ")在圆上" << endl;
        }
    }

private:
    Point mp;
    int mR;
};

void test01()
{
    //实例化圆
    Circle circle;
    circle.setP(20, 20);
    circle.setR(5);

    //实例化点对象
    Point point;
    point.setX(25);
    point.setY(20);

    circle.IsPointInCircle(point);
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}