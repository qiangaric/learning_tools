
#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-08 16:45:45
 * @LastEditors: sch
 * @LastEditTime: 2023-12-08 17:37:33
 */

// �������������
// ��������Զ�����������
class Person
{
    friend ostream &operator<<(ostream &cout, Person &p);

public:
    Person(int a, int b)
    {
        m_A = a;
        m_B = b;
    }

private:
    // ���ó�Ա�������� ��������� p.operator<<(cout)  p << cout
    // �������ó�Ա��������<< ���������Ϊ�޷�ʵ��cout�����
    // void operator<<(cout)
    // {
    // }
    int m_A;
    int m_B;
};

// class Person
// {
// public:
//     // ���ó�Ա�������� ��������� p.operator<<(cout)  p << cout
//     // �������ó�Ա��������<< ���������Ϊ�޷�ʵ��cout�����
//     // void operator<<(cout)
//     // {
//     // }
//     int m_A;
//     int m_B;
// };

// ֻ������ȫ�ֺ����������������
ostream &operator<<(ostream &cout, Person &p) // ���� operator<<(cout,p) ��cout<<p
{
    cout << "m_A = " << p.m_A << " m_B = " << p.m_B;
    return cout;
}

void test01()
{
    Person p(10, 10);
    // p.m_A = 10;
    // p.m_B = 10;
    cout << p << " hello , world" << endl;
}
int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
