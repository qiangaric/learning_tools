#include <iostream>

using namespace std;

/**
 * 构造函数和析构函数
 *对象的初始化和清理
 *1、构造函数，进行初始化操作
 *
 *
 */
class Person
{
    /**
     * 构造函数
     * 没有返回值，不用写void
     * 函数名 与类名相同
     * 构造函数可以有参数，可以发生重载
     * 创建对象的时候，析构函数会自动调用，并且只调用一次
     *
     */
private:
    /* data */
public:
    Person()
    {
        cout << "构造函数的调用" << endl;
    }

    //
    /**
     * 2、析构函数 进行清理的操作
     * 没有返回值 不写void
     * 函数名和类名相同 在名称前加~
     * 析构函数不可以有参数的，不可以发生重载
     * 对象在销毁前 会自动调用析构函数，而且只会调用一次
     *
     */
    ~Person()
    {
        cout << "Person 的析构函数调用" << endl;
    };
};

// Person::Person(/* args */)
// {
// }

// Person::~Person()
// {
// }

void test01()
{
    Person p; // 局部变量，在栈上的数据，test01执行完毕，释放这个对象
}

int main(int argc, char const *argv[])
{
    // test01();
    Person p;
    // system("pause");
    return 0;
}
