#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-14 16:11:22
 * @LastEditors: sch
 * @LastEditTime: 2023-12-14 16:22:25
 */

class Base
{
private:
    /* data */
public:
    Base(/* args */)
    {
        cout << "Base 构造函数" << endl;
    };
    ~Base()
    {
        cout << "Base 析构函数" << endl;
    };
};

class Son : public Base
{
private:
    /* data */
public:
    Son(/* args */)
    {
        cout << "Son 构造函数" << endl;
    };
    ~Son()
    {
        cout << "Son 析构函数" << endl;
    };
};

void test01()
{
    // Base b;
    // 先进后出
    // 先构造父类，再构造子类，析构的顺序与构造的顺序相反
    Son c;
}
int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
