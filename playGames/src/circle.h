#pragma onace
#include <iostream>
#include "point.h"
using namespace std;

class Circle
{
private:
    /* data */
    int m_R; // 半径
    // 在类中可以让另一个类 作为本类中的成员
    Point m_Center; // 圆心
public:
    void setR(int r);

    int getR();

    // 设置圆心
    void setCenter(Point center);

    // 获取圆心
    Point getCenter();
};