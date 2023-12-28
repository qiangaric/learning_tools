#pragma once
#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-27 11:20:49
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-27 11:28:25
 */

// 类文件的分文件编写

template <class T1, class T2>
class Person
{
private:
    /* data */
public:
    Person(T1 name, T2 age);
    void showPerson();
    T1 m_Name;
    T2 m_Age;
};
// 构造函数类外实现
template <class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
    this->m_Name = name;
    this->m_Age = age;
}
template <class T1, class T2>
void Person<T1, T2>::showPerson()
{
    cout << "name: " << this->m_Name << " age: " << this->m_Age << endl;
}