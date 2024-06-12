#include <iostream>
#include <string>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-25 10:55:25
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-25 11:15:03
 */

// 类模板对象做函数参数
template <class T1, class T2>
class Person
{
public:
    Person(T1 name, T2 age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    void showPerson()
    {
        cout << "name: " << this->m_Name << " age: " << this->m_Age << endl;
    }
    T1 m_Name;
    T2 m_Age;
};

// 1、指定传入类型

void printPerson1(Person<string, int> &p)
{
    p.showPerson();
};

void test01()
{
    Person<string, int> p1("gao", 100);
    printPerson1(p1);
}
// 2、参数模板化
template <class T1, class T2>
void printPerson2(Person<T1, T2> &p)
{
    p.showPerson();
    // cout << " T1 class type: " << typeid(T1).name() << endl;
    // cout << " T2 class type: " << typeid(T2).name() << endl;
};

void test02()
{
    Person<string, int> p2("chang", 90);
    printPerson2(p2);
}

// 3、整个类模板化

template <class T>
void printPerson3(T &p)
{
    p.showPerson();
};

void test03()
{
    Person<string, int> p3("li", 30);
    printPerson1(p3);
}

int main(int argc, char const *argv[])
{
    test01();
    test02();
    test03();
    return 0;
}
