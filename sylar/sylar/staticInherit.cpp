
#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-15 09:12:43
 * @LastEditors: sch
 * @LastEditTime: 2023-12-15 16:14:32
 */

// �̳��е�ͬ����̬��Ա����ʽ

class Base
{
private:
    /* data */
public:
    // ��̬����: ����׶η����ڴ� ���ж�����ͬһ������ �������������ʼ��
    static int m_A;
    static void func()
    {
        cout << "Base - func void func()" << endl;
    };
};

int Base::m_A = 100;

class Son : public Base
{
private:
    /* data */
public:
    static int m_A;

    static void func()
    {
        cout << "Son - func void func()" << endl;
    };
};

int Son::m_A = 200;

// ͬ����̬��Ա����
void test01()
{
    // ͨ���������
    cout << "ͨ���������: " << endl;
    Son s;
    cout << " m_A = " << s.m_A << endl;
    cout << "Base.m_A = " << s.Base::m_A << endl;

    // 2��ͨ����������
    cout << "ͨ����������: " << endl;
    cout << "son m_A = " << Son::m_A << endl;
    cout << "Base m_A = " << Son::Base::m_A << endl;
};
// ͬ����̬��Ա����

void test02()
{
    // 1��ͨ���������
    cout << "ͨ��������� " << endl;
    Son s;
    s.func();
    s.Base::func();

    // 2��ͨ����������
    cout << "ͨ���������� " << endl;
    Son::func();
    Son::Base::func();
};
int main(int argc, char const *argv[])
{
    // test01();
    test02();
    return 0;
}
