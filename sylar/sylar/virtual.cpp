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

// 纯虚函数和抽象类
class Base
{
public:
    // 纯虚函数
    // 只要一个纯虚函数，这个类称为抽象类
    //  抽象类特点:
    //  1、无法实例化对象
    // 2、 抽象类的子类，必须重写父类中的纯虚函数，否则也属于抽象类
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
    // Base b; // 抽象类无法实例化对象
    // Son s; // 子类必须重新写父类中的纯虚函数,否则无法实例化对象
    // s.func();

    // 堆区内存 手动开辟 手动释放

    Base *base = new Son;
    base->func();
    delete base;
}

int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
