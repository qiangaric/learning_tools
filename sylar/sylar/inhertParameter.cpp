
#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-14 17:45:59
 * @LastEditors: sch
 * @LastEditTime: 2023-12-14 18:05:34
 */

// 继承中同名成员处理
class Base
{
private:
    /* data */
public:
    Base(/* args */)
    {
        m_A = 100;
    };

    int m_A;

    void func()
    {
        cout << "Base -  func()调用" << endl;
    }
    // 函数重载
    void func(int a)
    {
        cout << "Base -  func(int a)调用" << endl;
    }
};
class Son : public Base
{

public:
    Son(/* args */)
    {
        m_A = 200;
    };

    void func()
    {
        cout << "Son -  func()调用" << endl;
    }
};
// 同名成员属性的处理方式
void test01()
{
    Son s;
    cout << " Son 下 m_A = " << s.m_A << endl;
    // 如果通过子类对象 访问到父类中同名成员 ，需要加作用域
    cout << " Base 下 m_A = " << s.Base::m_A << endl;
}
// 同名成员函数处理
void test02()
{
    Son s;
    s.func(); // 直接调用 调用是子类中的同名成员
    s.Base::func();

    // 如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类中所有同名函数
    s.Base::func(100);
}

int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
