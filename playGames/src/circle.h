#pragma onace
#include <iostream>
#include "point.h"
using namespace std;

class Circle
{
private:
    /* data */
    int m_R; // �뾶
    // �����п�������һ���� ��Ϊ�����еĳ�Ա
    Point m_Center; // Բ��
public:
    void setR(int r);

    int getR();

    // ����Բ��
    void setCenter(Point center);

    // ��ȡԲ��
    Point getCenter();
};