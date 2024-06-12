#include <iostream>
using namespace std;

class Person
{
private:
    /* data */
public:
    Person(/* args */)
    {
        cout << "Person的无参构造函数调用" << endl;
    };
    Person(int a)
    {
        age = a;
        cout << "Person的有参构造函数调用" << endl;
    };
    // 拷贝构造函数
    Person(const Person &p)
    {
        // 将传入的人身上的所有属性，拷贝到我身上
        age = p.age;
        cout << "Person的拷贝构造函数调用" << endl;
    };

    ~Person()
    {
        cout << "回收资源" << endl;
    };
    int age;
};

void test01()
{
    // Person p1;
    // 编译器会认为是一个函数的声明，不会认为在创建对象
    Person p1();
    Person p2(10);
    Person p3(p2);
    // 显示法
    Person p4;
    Person p5 = Person(10);
    Person p6 = Person(p5);

    // 隐士
    Person p7 = 10; // Person p7 = Person(10);
    Person p8 = p7;
};
int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
