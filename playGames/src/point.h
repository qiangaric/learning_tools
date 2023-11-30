// 防止头文件重复包含
#pragma once
#include <iostream>
using namespace std;

//点类 声明
class Point
{
private:
    int m_X;
    int m_Y;

public:
    void setX(int x);

    void setY(int y);

    int getX();

    int getY();
};
