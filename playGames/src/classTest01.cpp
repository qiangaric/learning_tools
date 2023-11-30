#include <iostream>
#include "circle.h"
#include "point.h"

using namespace std;

// //
// class Point
// {
// private:
//     int m_X;
//     int m_Y;

// public:
//     void setX(int x)
//     {
//         m_X = x;
//     };
//     void setY(int y)
//     {
//         m_Y = y;
//     };

//     int getX()
//     {
//         return m_X;
//     };
//     int getY()
//     {
//         return m_Y;
//     };
// };

// class Circle
// {
// private:
//     /* data */
//     int m_R;        // 半径
//     //在类中可以让另一个类 作为本类中的成员
//     Point m_Center; // 圆心
// public:
//     void setR(int r)
//     {
//         m_R = r;
//     };

//     int getR()
//     {
//         return m_R;
//     };
//     // 设置圆心
//     void setCenter(Point center)
//     {
//         m_Center = center;
//     }
//     // 获取圆心
//     Point getCenter()
//     {
//         return m_Center;
//     }
// };

void isIncircle(Circle &c, Point &p)
{
    // 计算两点之前的距离
    int distance =
        (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) +
        (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());

    // 计算半径的平方
    int rDistance = c.getR() * c.getR();

    // 判断关系
    if (distance == rDistance)
    {
        cout << "点在圆上" << endl;
    }
    else if (distance > rDistance)
    {
        cout << "点在圆外" << endl;
    }
    else
    {
        cout << "点在圆内" << endl;
    }
}

int main(int argc, char const *argv[])
{
    // 创建圆
    Circle c;
    c.setR(10);
    Point center;
    center.setX(10);
    center.setY(0);
    c.setCenter(center);
    // 创建点
    Point p;
    p.setX(10);
    p.setY(10);

    // 判断关系
    isIncircle(c, p);
    return 0;
}
