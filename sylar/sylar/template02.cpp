#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-25 10:38:40
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-25 10:49:02
 */

class Person1
{
private:
    /* data */
public:
    void showPerson1()
    {
        cout << " Person1 show" << endl;
    }
};

class Person2
{
private:
    /* data */
public:
    void showPerson2()
    {
        cout << " Person2 show" << endl;
    }
};

template <class T>
class MyClass
{
public:
    T obj;
    // ��ģ���еĳ�Ա������������һ��ʼ�ʹ����ģ�������ģ�����ʱ������
    void fun1()
    {
        obj.showPerson1();
    }
    void fun2()
    {

        obj.showPerson2();
    }
};

void test01()
{
    MyClass<Person2> m;
    // m.fun1();
    m.fun2();
};

int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
