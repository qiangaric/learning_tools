
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

// 继承中的同名静态成员处理方式

class Base
{
private:
    /* data */
public:
    // 静态属性: 编译阶段分配内存 所有对象共享同一份数据 类内声明类外初始化
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

// 同名静态成员属性
void test01()
{
    // 通过对象访问
    cout << "通过对象访问: " << endl;
    Son s;
    cout << " m_A = " << s.m_A << endl;
    cout << "Base.m_A = " << s.Base::m_A << endl;

    // 2、通过类名访问
    cout << "通过类名访问: " << endl;
    cout << "son m_A = " << Son::m_A << endl;
    cout << "Base m_A = " << Son::Base::m_A << endl;
};
// 同名静态成员函数

void test02()
{
    // 1、通过对象访问
    cout << "通过对象访问 " << endl;
    Son s;
    s.func();
    s.Base::func();

    // 2、通过类名访问
    cout << "通过类名访问 " << endl;
    Son::func();
    Son::Base::func();
};
int main(int argc, char const *argv[])
{
    // test01();
    test02();
    return 0;
}
