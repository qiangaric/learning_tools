#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-21 16:53:11
 * @LastEditors: sch
 * @LastEditTime: 2023-12-21 17:23:30
 */

// ���麯���ͳ�����
class Base
{
public:
    // ���麯��
    // ֻҪһ�����麯����������Ϊ������
    //  �������ص�:
    //  1���޷�ʵ��������
    // 2�� ����������࣬������д�����еĴ��麯��������Ҳ���ڳ�����
    virtual void func() = 0;
};

class Son : public Base
{
public:
    void func()
    {
        cout << " redefine" << endl;
    }
};

void test02()
{
    // Base b; // �������޷�ʵ��������
    // Son s; // �����������д�����еĴ��麯��,�����޷�ʵ��������
    // s.func();

    // �����ڴ� �ֶ����� �ֶ��ͷ�

    Base *base = new Son;
    base->func();
    delete base;
}

int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
